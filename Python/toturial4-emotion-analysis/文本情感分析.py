#!/usr/bin/env python
# coding: utf-8

# In[4]:


#对评论文本去重
import pandas as pd
import re
#读取采集的iPhoneX评论数据
Data = pd.read_csv("C:/Users/iPhoneX_comment.csv",sep =",",encoding = "utf-8")
Data["页面标题"].value_counts()#返回包含值和该值出现次数的Series对象


# In[5]:


#删除冗余属性，返回一个新对象
iPhoneX_comment_new = Data.drop(labels=["会员","级别","评价星级","时间","点赞数","评论数","追评时间","追评内容","页面网址","页面标题","采集时间"],axis=1)
iPhoneX_comment_new.head(2)  #获取删除冗余属性后的前两条记录


# In[7]:


iPhoneX_comment_new.duplicated().sum()  #统计重复的文本数


# In[8]:


#去除6行重复评论
iPhoneX_comment_unique = iPhoneX_comment_new.drop_duplicates()
iPhoneX_comment_unique.shape


# In[9]:


#编译正则表达式对象，用于去除高频无意义的词
strinfo = re.compile("手机|苹果|店家|京东|东西|n")  
iPhoneX_comment_useless = iPhoneX_comment_unique["评价内容"].apply(lambda x:strinfo.sub("",x))


# In[10]:


def condense(str):
    for i in [1, 2]:
        j = 0
        while j < len(str)-2*i:
            #判断重复了至少两次                                                                                                                                                                           
            if str[j:j+i]==str[j+i:j+2*i] and str[j:j+i]==str[j+2*i: j+3*i]:
                k = j+2*i
                while k+i<len(str) and str[j: j+i]==str[k+i: k+2*i]:
                    k += i
                str = str[: j+i] + str[k+i:]
            j += 1
        i += 1
    for i in [3, 4, 5]:
        j = 0
        while j< len(str)-2*i:
            #判断重复了至少一次
            if str[j: j+i]==str[j+i: j+2*i]:
                k = j+i
                while k+i<len(str) and str[j: j+i]==str[k+i: k+2*i]:
                    k += i
                str = str[: j+i] + str[k+i:]
            j += 1
        i += 1
    return str
iPhoneX_comment_compress=iPhoneX_comment_useless.astype("str").apply(lambda x:condense(x))      #机械压缩去词

length = iPhoneX_comment_compress.apply(lambda x:len(x)) #统计每条评论的字数
#下面的语句将iPhoneX_comment_compress和length连接，生成一个新的对象
DataClear = pd.concat([iPhoneX_comment_compress,length],axis=1) 
DataClear.columns = ["iPhoneX评论","评论长度"]   #重新命名列名
DataClear.head(5)     #获取前5条记录


# In[11]:


#短句删除
Conment = DataClear[DataClear["评论长度"] > 5]  #删除评论长度<6的评论


# In[13]:


#利用jieba分词包对评论文本进行中文分词。
import jieba
wordsCut=Conment["iPhoneX评论"].astype("str").apply(lambda x: list(jieba.cut(x)))
wordsCut[:10]


# In[21]:


#加载停用词表，sep设置为文档内不包含的内容，否则会出错
stopWords  = pd.read_csv("D:\\Python\\stoplist.txt",sep = "fenci",encoding ="utf-8",header = None)
stopWords = list(stopWords[0]) + [" ", ""]  #向stopWords里添加空格符
#去除停用词
wordStop = wordsCut.apply(lambda x:[i for i in x if i not in stopWords])


# In[23]:


#下面给出绘制评论文本的词云图的代码实现。
from imageio import imread
from wordcloud import WordCloud,ImageColorGenerator
import matplotlib.pyplot as plt  
wordTemp = []
for i in wordStop.index:
    wordTemp.extend(wordStop.loc[i])
wordStop_df = pd.DataFrame(wordTemp)
wordStop_df.columns = ["words"]
result= "/".join(wordTemp)
plt.rcParams['figure.figsize'] = (10.0, 10.0)
#自定义词云背景图片
image =imread("D:\\Python\\tupian.jpg")
#构建词云模型
wordcloud = WordCloud(background_color="white", mask=image,font_path=r"C:\Windows\Fonts\simhei.ttf", max_font_size=200)
wordcloud.generate(result) 
image_color = ImageColorGenerator(image)  #从背景图片生成词云图中文字的颜色
wordcloud.recolor(color_func=image_color)
#保存绘制好的词云图，比直接程序显示的图片更清晰
wordcloud.to_file(r"D:\Python\wordcloud.png")  
#显示词云图图片
plt.figure("词云图")   #指定所绘图名称
plt.imshow(wordcloud)  #以图片的形式显示词云
plt.axis("off")        # 关闭图像坐标系
plt.show()


# In[17]:


#评论文本情感倾向分析
#读取情感字典文件
feeling = pd.read_csv("D:\\Python\\BosonNLP.txt",sep = " ",encoding = "utf-8",header =None)
feeling.columns = ["word","score"]    #重新命名列名
print('feeling的前5行：\n',feeling.head(5))


# In[19]:


#导入否定词词库，并新增1列为'value'，取值全部为-1
notdict = pd.read_csv("D:\\Python\\not.csv",encoding='utf-8')
notdict['value']=-1
print('notdict的前5行：\n',notdict.head(5))


# In[24]:


#将wordStop_df，否定词表，词语情感分值表合并
df = pd.merge(wordStop_df,notdict,how='left',left_on='words', right_on='term')
df = pd.merge(df,feeling,how= 'left',left_on = 'words',right_on='word')
df.drop(['term','word'],axis=1,inplace= True)
print('df的前5行：\n',df.head(5))


# In[25]:


#统计每条记录的词语数目，方便后续判断每个词语的句子归属
length=[len(wordStop.iloc[i]) for i in range(wordStop.shape[0])]
#给各词语指定归属标号，即词语所属记录的序号
ID = []
for i in range(len(length)):
    ID.extend([i]*length[i])
#将ID作为df的index
df.index = ID
print('将ID作为df的index后的df的前5行：\n',df.head(5))


# In[26]:


#获取不含有否定词的句子的ID
noneNotId = list(df.loc[df['value'].isnull(),:].index)
#新建pandas对象存放句子的情感分值
dfScore = pd.DataFrame(index = list(set(df.index)),columns = ['Score'])
#将没有否定词的句子的所有词的情感分值相加
for i in noneNotId:
    dfScore.loc[i,'Score'] = df.loc[i,'score'].sum()
print('dfScore的前5行：\n',dfScore.head(5))


# In[27]:


#取出含有否定词的句子ID
NotID = list(set(df.loc[df['value'].notnull(),:].index))
#以value为基础合并，若df['value']的数据缺失,则用df['score']的数据值填充
df['score1'] = df['value'].combine_first(df['score'])
df['score1'] = df['score1'].fillna(0)   #用0填充nan数据
print('以value为基础合并后的df的前5行：\n',df.head(5))


# In[28]:


NotScore = []
for i in NotID:
    score = 0
    Ser = df.loc[i,'score1']  #取出其中一个有否定词句子的index和score1
    lenNot = Ser.shape[0]     #获取句子包含的总共词语数目
    cirlist = [k for k in range(lenNot)]
    cirlist .reverse()
    #从后往前计算一个句子的情感分值，防止最前面出现否定词无效
    for j in cirlist: 
        if  Ser.iloc[j] == -1: #若句子的最后一个词为否定词，Score初始化为-1
            if j == (lenNot-1):
                score = -1
            elif (j ==0) & (Ser.iloc[j+1]!=-1):
                #在遇见-1时，前项已经加过，因而应将前项减去再加上(-1*得分)
                score = score- Ser.iloc[j] + (-1* Ser.iloc[j])
            else:
                if (Ser.iloc[j+1]!=-1) & (Ser.iloc[j-1]!=-1):
                    score = score- Ser.iloc[j] + (-1* Ser.iloc[j])
                    #在双重否定的情况下，不需要做操作
                    #本算法不考虑多重否定
        else:
            score += Ser.iloc[j]
    NotScore.append(score)
dfScore.loc[NotID,'Score'] = NotScore
wordStop=wordStop.reset_index(drop=True)
feelScore = pd.concat([dfScore,wordStop],axis = 1)
pos = feelScore.loc[feelScore['Score'] > 0,['Score','iPhoneX评论']]
print('pos的前5行\n',pos.head(5))
neg = feelScore.loc[feelScore['Score'] < 0,['Score','iPhoneX评论']]
print('neg的前5行\n',neg.head(5))


# In[30]:


#下面给出评论文本的LDA主题分析的代码实现
from gensim import corpora, models
pos = feelScore.loc[feelScore['Score'] > 0,'iPhoneX评论']
neg = feelScore.loc[feelScore['Score'] < 0,'iPhoneX评论']
#负面主题分析
neg_dict = corpora.Dictionary(neg)              #建立负面词典
neg_corpus = [neg_dict.doc2bow(i) for i in neg] #建立负面语料库
#构建LDA模型
neg_lda = models.LdaModel(neg_corpus, num_topics = 3, id2word = neg_dict) 
print("\n负面评价")
for i in range(3):
    print("主题%d : " %i)
    print(neg_lda.print_topic(i) ) #输出主题
#正面主题分析
pos_dict = corpora.Dictionary(pos)
pos_corpus = [pos_dict.doc2bow(i) for i in pos]
pos_lda = models.LdaModel(pos_corpus, num_topics = 3, id2word = pos_dict)
print("\n正面评价")
for i in range(3):
    print("主题%d : " %i)
    print(pos_lda.print_topic(i) ) #输出主题


# In[ ]:




