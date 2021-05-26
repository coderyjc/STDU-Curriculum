/**
 * @Author: Yan Jingcun
 * @Date: 2021/5/26
 * @Description:
 * @Version: 1.0
 */

package com.jancoyan.lab2_2.utils;

public class UserLocationUtil {

    public static String getLocation(Integer locationId){
        String location = "null";
        if (locationId == 0){
            location = "北京";
        } else if (locationId == 1){
            location = "上海";
        }else if (locationId == 2){
            location = "广州";
        }else if (locationId == 3){
            location = "深圳";
        }else if (locationId == 4){
            location = "杭州";
        }

        return location;
    }

}
