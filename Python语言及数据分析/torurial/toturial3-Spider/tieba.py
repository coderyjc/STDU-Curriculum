"""
Author: Yan Jingcun
Date: 2022-05-02
Time: 10:57:48
Description: 爬取数据并保存
"""

from lxml import etree
from selenium import webdriver
from selenium.webdriver.common.by import By
from time import sleep

bro = webdriver.Firefox(executable_path='./utils/geckodriver.exe', firefox_binary='U://FireFox/Firefox/firefox.exe')

url = 'https://book.douban.com/subject/5363767/reviews?start=20'

bro.get(url)
list_elements = bro.find_elements(by=By.CLASS_NAME, value="unfold")

# 这个页面一共的元素
element_number = len(list_elements)

with open('content2.txt', 'w+', encoding='utf-8') as f:

  # 打开每一个节点, 中间显式等待
  for i in range(element_number):
    list_elements = bro.find_elements(by=By.CLASS_NAME, value="unfold")[i].click()
    sleep(2)
    # 点击展开之后查找目标元素
    xpath = '//*[@class="review-content clearfix"]/text()'
    page_text = bro.page_source
    tree = etree.HTML(page_text)
    text = tree.xpath(xpath)
    for content in text:
      f.write(content)
    # 刷新页面
    bro.refresh()

bro.quit()