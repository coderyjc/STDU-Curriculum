"""
Author: Yan Jingcun
Date: 2022-05-13
Time: 20:09:58
Description: 进入页面爬取图书类别
"""

import requests
from lxml import etree
from time import sleep
import random
from selenium import webdriver
from selenium.webdriver.common.by import By
from sqlalchemy import null
import sys

fp = open("./urls.txt", "r", encoding='utf-8')
fpw = open("./types.txt", "w+", encoding='utf-8')

books_url = fp.readlines()

bro = webdriver.Firefox(executable_path='./utils/geckodriver.exe', firefox_binary='U://FireFox/Firefox/firefox.exe')

DangUserName = '18731123320'
DangPassword = 'Angel75574609'
flag = 0
for book in books_url:
  url = book[:-1]
  bro.get(url)
  tree = etree.HTML(bro.page_source)

  # 遇到反爬登录
  if tree.xpath('//*[@id="detail-category-path"]//text()') == []:
    print("--遭遇反爬--模拟登录--")
    # 用bro的查找，不能用xpath
    username = bro.find_element(by=By.XPATH, value='/html/body/div/div[2]/div/div/div[1]/div/div/div[3]/div/div[1]/div[1]/input')
    password = bro.find_element(by=By.XPATH, value='/html/body/div/div[2]/div/div/div[1]/div/div/div[3]/div/div[2]/div[1]/input')
    # 填写用户名
    username.click()
    username.send_keys(DangUserName)
    # 填写密码
    password.click()
    password.send_keys(DangPassword)
    # 点击登录按钮
    bro.find_element(by=By.CLASS_NAME, value='btn').click()
    sleep(20)
    if flag == 2:
      sys.exit(0)
    flag = flag + 1

  booktype = tree.xpath('//*[@id="detail-category-path"]//text()')
  for str in booktype:
    fpw.write(str)
  fpw.write('\n')
  # 随机休眠，避免被封
  sleep(random.randint(0, 30) / 10)
  print(url, booktype)

fp.close()
fpw.close()