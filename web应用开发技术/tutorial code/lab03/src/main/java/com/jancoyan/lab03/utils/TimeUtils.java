/**
 * @Author: Yan Jingcun
 * @Date: 2021/5/28
 * @Description:
 * @Version: 1.0
 */

package com.jancoyan.lab03.utils;

import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;

public class TimeUtils {

    /**
     * 将java Date 将对象转化为日期字符串形式
     * @param date
     * @return
     */
    public static String castDateTypeToDateString(Date date){
        SimpleDateFormat simpleDateFormat = new SimpleDateFormat("yyyy-MM-dd");
        return simpleDateFormat.format(date);
    }


    /**
     * 把日期字符串转化为 yyyy-MM-dd 日期类型
     * @param dateStr 日期字符串
     * @return 日期类型
     */
    public static Date castDateStringToDateTypeYMD(String dateStr){
        Date date = null;
        SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd");
        try {
            date = sdf.parse(dateStr);
        } catch (ParseException e) {
            e.printStackTrace();
        }
        return date;
    }

}
