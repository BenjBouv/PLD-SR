(function ($) {
    $.format = (function () {
	
        var parseMonth = function (value) {
            switch (value) {
                case "Jan":
                    return "01";
                case "Feb":
                    return "02";
                case "Mar":
                    return "03";
                case "Apr":
                    return "04";
                case "May":
                    return "05";
                case "Jun":
                    return "06";
                case "Jul":
                    return "07";
                case "Aug":
                    return "08";
                case "Sep":
                    return "09";
                case "Oct":
                    return "10";
                case "Nov":
                    return "11";
                case "Dec":
                    return "12";
                default:
                    return value;
            }
        };

        var parseTime = function (value) {
            var retValue = value;
            if (retValue.indexOf(".") !== -1) {
                retValue = retValue.substring(0, retValue.indexOf("."));
            }

            var values3 = retValue.split(":");

            if (values3.length === 3) {
                hour = values3[0];
                minute = values3[1];
                second = values3[2];

                return {
                    time: retValue,
                    hour: hour,
                    minute: minute,
                    second: second
                };
            } else {
                return {
                    time: "",
                    hour: "",
                    minute: "",
                    second: ""
                };
            }
        };

        return {
			settings: {
			  strings: {
				months: ["Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"],
				days: ["Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"],
				ordinal: ["th", "st", "nd", "rd"]
			  }
			},
		
            date: function (value, format) {
                //value = new java.util.Date()
                //2009-12-18 10:54:50.546
                try {
					var $strings = this.settings.strings;
                    var year = null;
                    var month = null;
                    var dayOfMonth = null;
					var dayOfWeek = null;
                    var time = null; //json, time, hour, minute, second
                    if (typeof value.getFullYear === "function") {
                        year = value.getFullYear();
                        month = value.getMonth() + 1;
						dayOfWeek = value.getDay();
                        dayOfMonth = value.getDate();
                        time = parseTime(value.toTimeString());
                    } else if (value.search(/\d{4}-\d{2}-\d{2}T\d{2}:\d{2}:\d{2}\.?\d{0,3}\+\d{2}:\d{2}/) != -1) { // 2009-04-19T16:11:05+02:00
                        var values = value.split(/[T\+-]/);
                        year = values[0];
                        month = values[1];
                        dayOfMonth = values[2];
						dayOfWeek = new Date(year, month, dayOfMonth).getDay();
                        time = parseTime(values[3].split(".")[0]);
                    } else {
                        var values = value.split(" ");
                        switch (values.length) {
                            case 6: //Wed Jan 13 10:43:41 CET 2010
                                year = values[5];
                                month = parseMonth(values[1]);
                                dayOfMonth = values[2];
                                time = parseTime(values[3]);
                                break;
                            case 2: //2009-12-18 10:54:50.546
                                var values2 = values[0].split("-");
                                year = values2[0];
                                month = values2[1];
                                dayOfMonth = values2[2];
                                time = parseTime(values[1]);
                                break;
						    case 7: // Tue Mar 01 2011 12:01:42 GMT-0800 (PST)
	                            year = values[3];
	                            month = parseMonth(values[1]);
	                            dayOfMonth = values[2];
	                            time = parseTime(values[4]);
	                            break;
                            default:
                                return value;
                        }
						dayOfWeek = new Date(year, month, dayOfMonth).getDay();
                    }

                    var pattern = "";
                    var retValue = "";
                    //Issue 1 - variable scope issue in format.date 
                    //Thanks jakemonO
                    for (var i = 0; i < format.length; i++) {
                        var currentPattern = format.charAt(i);
                        pattern += currentPattern;
                        switch (pattern) {
                            case "dd":
                                retValue += dayOfMonth;
                                pattern = "";
                                break;
							case "th":
								var moduloDay = dayOfMonth % 10;
								if ((moduloDay > 0) && (moduloDay < 4)) {
									retValue += $strings.ordinal[moduloDay];
								} else {
									retValue += $strings.ordinal[0];
								}
                                pattern = "";
                                break;
							case "DD":
								retValue += $strings.days[dayOfWeek];
                                pattern = "";
                                break;
                            case "MMM":
                                retValue += $strings.months[month-1];
                                pattern = "";
                                break;
                            case "MM":
                                if (format.charAt(i+1) == "M") {
                                    break;
                                }
                                retValue += month;
                                pattern = "";
                                break;
                            case "yyyy":
                                retValue += year;
                                pattern = "";
                                break;
                            case "HH":
                                retValue += time.hour;
                                pattern = "";
                                break;
                            case "hh":
                                //time.hour is "00" as string == is used instead of ===
                                retValue += (time.hour == 0 ? 12 : time.hour < 13 ? time.hour : time.hour - 12);
                                pattern = "";
                                break;
                            case "mm":
                                retValue += time.minute;
                                pattern = "";
                                break;
                            case "ss":
                                //ensure only seconds are added to the return string
                                retValue += time.second.substring(0, 2);
                                pattern = "";
                                break;
                            //case "tz":
                            //    //parse out the timezone information
                            //    retValue += time.second.substring(3, time.second.length);
                            //    pattern = "";
                            //    break;
                            case "a":
                                retValue += time.hour >= 12 ? "PM" : "AM";
                                pattern = "";
                                break;
                            case " ":
                                retValue += currentPattern;
                                pattern = "";
                                break;
                            case "/":
                                retValue += currentPattern;
                                pattern = "";
                                break;
                            case ":":
                                retValue += currentPattern;
                                pattern = "";
                                break;
                            default:
                                if (pattern.length === 2 && pattern.indexOf("y") !== 0) {
                                    retValue += pattern.substring(0, 1);
                                    pattern = pattern.substring(1, 2);
                                } else if ((pattern.length === 3 && pattern.indexOf("yyy") === -1)) {
                                    pattern = "";
                                }
                        }
                    }
                    return retValue;
                } catch (e) {
                    console.log(e);
                    return value;
                }
            }
        };
    } ());
} (jQuery));


$(document).ready(function () {
    $(".shortDateFormat").each(function (idx, elem) {
        if ($(elem).is(":input")) {
            $(elem).val($.format.date($(elem).val(), 'dd/MM/yyyy'));
        } else {
            $(elem).text($.format.date($(elem).text(), 'dd/MM/yyyy'));
        }
    });
    $(".longDateFormat").each(function (idx, elem) {
        if ($(elem).is(":input")) {
            $(elem).val($.format.date($(elem).val(), 'dd/MM/yyyy hh:mm:ss'));
        } else {
            $(elem).text($.format.date($(elem).text(), 'dd/MM/yyyy hh:mm:ss'));
        }
    });
});
