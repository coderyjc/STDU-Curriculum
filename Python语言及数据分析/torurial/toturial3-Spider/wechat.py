# -!- coding: utf-8 -!-

from selenium import webdriver
from selenium.webdriver.common.by import By


#加载chromedriver
driver = webdriver.Firefox(executable_path='./utils/geckodriver.exe', firefox_binary='U://FireFox/Firefox/firefox.exe')
#进入主页
url = 'http://weixin.sogou.com/'
driver.get(url)
input = driver.find_element(By.XPATH,'//*[@id="query"]')
input.send_keys('三体')
#点击“搜文章”按钮
button = driver.find_element(By.CLASS_NAME, 'swz')
button.click()
# link_list用于保存每个文章的url链接
link_list = list()
#遍历前10页的内容
for page in range(1):
#每一页有10篇文章
   for i in range(10):
      try:
         #动态生成文章题目的xpath
         id ='sogou_vr_11002601_title_' + str(i)
         # 使用get_attribute ()方法获取href属性值
         title = driver.find_element(By.ID, id).get_attribute('href')
         #把获取到的链接保存到link_list中去
         link_list.append(title)
      except:
         continue
   #使用 “下一页” 按钮进行翻页
   if page != 9:
      next = driver.find_element(By.ID, 'sogou_next')
      next.click()
   else:
      break

#打开文件result2.txt，把获取的内容写入其中
with open('result2.txt', 'w', encoding='utf-8') as result:
    for link in link_list:
        try:
            #打开文章页面
            driver.get(link)
            #获取元素的文本内容，使用.text来获取
            title = driver.find_element(By.ID, 'activity-name').text
            id = driver.find_element(By.ID, 'js_name').text
            date = driver.find_element(By.ID, 'publish_time').text
            content = driver.find_element(By.ID, 'js_content').text
            msg = date + '\t' + id+'\t' + title + '\n' +content + '\n' + '---'*60
            print(msg)
            #写入文件
            result.write(msg+'\n')
        except:
            continue

#关闭chromedriver
driver.close()
