#include <mysql/mysql.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mysqlinsert.h"

MYSQL* connectToMysql() {
	MYSQL* mysql = mysql_init(NULL);
	if(mysql == NULL) {
		puts("Erreur de mysql_init");
	}
	
	long res = 0;
	int i;
	//Test 3 times to connect to mysql
	for(i=0; !res && i<3; i++) {
		if(i!=0) {
			sleep(1);
		}
		printf("try %d\n", i);
		res = (long)(mysql_real_connect(mysql,"localhost","rithm","rithm","pld",0,NULL,0));
	}

	if (!res) {
		fprintf(stderr, "Error: failed to connect to database (%s)\n", mysql_error(mysql));
	}
	
	if(mysql_query(mysql, "SET NAMES 'utf8'")) {
		printf("Erreur: SET NAMES 'utf8' (%s)\n", mysql_error(mysql));
	}
	
	return mysql;
}

void closeMysql(MYSQL* mysql) {
	mysql_close(mysql);
}

void insertCapteur(MYSQL* mysql, int type, int numeroCapteur, int isGlobal, int idSujet) {
	char s[512];
	sprintf(s, "INSERT INTO capteurs (type, numeroCapteur, isGlobal, idSujet) VALUES (%d, %d, %s, %d)",
			type, numeroCapteur, (isGlobal == 0 ? "false" : "true"), idSujet);

	if(mysql_query(mysql, s)) {
		printf("Erreur: insert (%s)\n", mysql_error(mysql));
	}
}

result* getCapteurs(MYSQL* mysql) {
	MYSQL_RES *mysqlResult;
	MYSQL_ROW row;
	int i;
	result* res;
	
	mysql_query(mysql, "SELECT type, numeroCapteur, isGlobal, idSujet FROM capteurs");
	mysqlResult = mysql_store_result(mysql);

	int nfields = mysql_num_fields(mysqlResult);
	int nrows = mysql_num_rows(mysqlResult);
	
	res = (result*) malloc(sizeof(result));
	res->nbFields = nfields;
	res->nbRows = nrows;
	res->tab = (int**) malloc(sizeof(int**)*nrows);

	int cpt = 0;
	while ((row = mysql_fetch_row(mysqlResult))) {
		res->tab[cpt] = (int*) malloc(sizeof(int*)*nfields);
		for(i = 0; i < nfields; i++) {
			res->tab[cpt][i] = row[i] ? atoi(row[i]) : 0;
			printf("%s ", row[i] ? row[i] : "NULL");
		}
		cpt++;
		printf("\n");
	}

	mysql_free_result(mysqlResult);
	return res;
}

void insertMesure(MYSQL* mysql, int type, int numeroCapteur, long long time, int typeMesure, double mesure) {
	char s[512];
	sprintf(s, "INSERT INTO mesures (idCapteur, time, typeMesure, mesure) VALUES ((SELECT id FROM capteurs WHERE numeroCapteur=%d),%lld,%d,%f)", numeroCapteur, time, typeMesure, mesure);
	//printf(s);
	if(mysql_query(mysql, s)) {
		printf("Erreur: insert (%s)\n", mysql_error(mysql));
	}
}

void insertActionneur(MYSQL* mysql, int num, int type) {
	char s[512];
	sprintf(s, "INSERT INTO actionneurs (numeroActionneur, type) VALUES (%d, %d)", num, type);

	if(mysql_query(mysql, s)) {
		printf("Erreur: insert (%s)\n", mysql_error(mysql));
	}
}

void insertActionneurSujet(MYSQL* mysql, int nom, char* description, int isGlobal, int idSujet) {
	char s[512];
	sprintf(s, "INSERT INTO actionneurSujet (nom, description, isGlobal, idSujet) VALUES ('%d', '%s', %s, %d)",
			nom, description, (isGlobal == 0 ? "false" : "true"), idSujet);

	if(mysql_query(mysql, s)) {
		printf("Erreur: insert (%s)\n", mysql_error(mysql));
	}
}

void insertPieces(MYSQL* mysql, char* nom, char* description) {
	char s[512];
	sprintf(s, "INSERT INTO pieces (nom, description) VALUES ('%s', '%s')", nom, description);

	if(mysql_query(mysql, s)) {
		printf("Erreur: insert (%s)\n", mysql_error(mysql));
	}
}

void insertPatients(MYSQL* mysql, char* nom, int isMan, char* raisonHospitalisation, int idPiece) {
	char s[512];
	sprintf(s, "INSERT INTO patients (nom, isMan, raisonHospitalisation, idPiece) VALUES ('%s', %s, '%s', %d)", nom, (isMan == 0 ? "false" : "true"), raisonHospitalisation, idPiece);

	if(mysql_query(mysql, s)) {
		printf("Erreur: insert (%s)\n", mysql_error(mysql));
	}
}
