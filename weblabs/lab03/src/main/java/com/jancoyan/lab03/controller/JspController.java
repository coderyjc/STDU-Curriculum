/**
 * @Author: Yan Jingcun
 * @Date: 2021/5/28
 * @Description:
 * @Version: 1.0
 */

package com.jancoyan.lab03.controller;

import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class JspController {

    @GetMapping("/index")
    public String index(){
        return "index";
    }


}
