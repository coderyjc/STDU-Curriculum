package com.jancoyan.lab2_1;

import java.io.*;
import javax.servlet.ServletException;
import javax.servlet.http.*;
import javax.servlet.annotation.*;

@WebServlet(name = "loginServlet", value = "/login")
public class LoginServlet extends HttpServlet {

    public void doPost(HttpServletRequest request,
                      HttpServletResponse response) throws IOException {
        System.out.println(request.getAttribute("userName"));
        response.sendRedirect("judge.jsp");
    }

}