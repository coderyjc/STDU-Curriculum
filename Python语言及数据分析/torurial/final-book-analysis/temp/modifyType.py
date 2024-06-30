"""
Author: Yan Jingcun
Date: 2022-05-14
Time: 22:40:25
Description: 
"""

typelines = open('./temp/types.txt', 'r', encoding='utf-8').readlines()

fpw = open('./temp/types-modified.txt', 'w+', encoding='utf-8')

for types in typelines:
  splits = types.split(' ')
  fpw.write(splits[0] + ',' + splits[1])
  fpw.write('\n')
fpw.close()