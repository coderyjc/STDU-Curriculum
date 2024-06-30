import requests
from bs4 import BeautifulSoup
import jieba
import re

##第一步我们需要构造请求，获取页面内容
url = "https://www.sohu.com/a/226127592_139908"
responce = requests.get(url)
soup = BeautifulSoup(responce.text, 'lxml')  #lxml用来解析网页
responce.status_code  #如果返回值为200则表示访问成功
##抓取页面，获取关键信息，目标是获取政府报告的全文，注意到这部分文本在 article类的article标签下，##可以利用BeautifulSoup模块下的find函数进行查找
links_div = soup.find("article", class_="article")
#print(links_div)    #我们可以尝试输出下获取的文本，验证是否是我们想要的
text = links_div.strip()  #对字符串进行切片操作，如果报错注释此行代码，运行text = links_div
#text = links_div
##得到的页面内容作为对象保存到字典中，然后再写入到本地的txt文档中
dic = {text}
with open("C:\\Users\Lenovo\\Desktop\\pictures\\report.txt",
          'a',
          encoding='utf-8') as f:
    f.write(str(dic))
f.close()
#注意到获取的页面内容中有html的标签和其他符号存在，不利于下一步的词云操作，所以需要利用jieba和##正则表达式对得到的文本进行清洗
r = '[，。\%、；1234567890n]'
file = open("C:\\Users\Lenovo\\Desktop\\pictures\\report.txt",
            "r",
            encoding='utf-8').read()
file = re.sub(r, '', file)  #剔除无关信息
con = jieba.lcut(file)  #分词
words = " ".join(con)  #分词后插入空格
#词云分析
from wordcloud import WordCloud

wordcloud = WordCloud(font_path="simkai.ttf",
                      background_color="white",
                      width=800,
                      height=660).generate(words)
#我们注意到wordcloud对中文很不友好，必须要进行jieba分词，还应该再WordCloud中增加设置字体的参数
#否则生成的词云图片是方框型的
wordcloud.to_file('pic.png')  #保存图片
