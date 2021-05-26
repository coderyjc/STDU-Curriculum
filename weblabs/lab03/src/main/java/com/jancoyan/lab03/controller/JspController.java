/**
 * @Author: Yan Jingcun
 * @Date: 2021/5/26
 * @Description:
 * @Version: 1.0
 */

package com.jancoyan.lab03.controller;

import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;

@Controller
public class JspController {

    @GetMapping("/index")
    public String index(){
        return "index";
    }

}
