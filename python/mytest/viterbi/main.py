#coding:utf8

import numpy as np
import pdb

def getMaxIndex(list):
    maxi = 0
    for i in range(1,len(list)):
        if list[i] > list[maxi]:
            maxi = i
    return maxi
        

def viterbi(trainsition_probability, emission_probability, pi, obs_seq):
    #转换为矩阵进行运算
    trainsition_probability = np.array(trainsition_probability)
    emission_probability = np.array(emission_probability)
    pi = np.array(pi)
    # 最后返回一个Row*Col的矩阵结果
    Row = np.array(trainsition_probability).shape[0]
    Col = len(obs_seq)
    #定义要返回的矩阵
    F = np.zeros((Row, Col))
    #整个viterbi的过程就是填一个M x N维的矩阵
    #行数M为隐含状态数 列数N为观察序列数
    #填矩阵的过程是从上到下，从左到右  即根据第一个观测值填第一列,根据第二个观测值填第二列....以此类推
    #初始状态(填第一列)
    F[:,0] = pi*np.transpose(emission_probability[:,obs_seq[0]])
    state_max2 = []
    for t in range(1,Col): #对观察值遍历(第一个已经用来生成初始状态了，不用处理了)
        list_max = []
        state_max = []
        for n in range(Row): #转移矩阵的行数遍历(即隐状态个数)
            list_x = np.array(F[:,t-1]) * np.transpose(trainsition_probability[:,n]) #由前一个状态转为当前n状态的概率
            #获取最大概率,也就是说前面哪个状态到本状态的概率最大，因为前面只能有一个状态所以取最大的，不能相加
            list_p = []
            max_value = 0
            max_index = 0
            for i in range(len(list_x)):
                list_p.append(list_x[i]*10000)
                if max_value <= list_x[i]:
                    max_index = i
                    max_value = list_x[i]
            state_max.append(max_index);
            list_max.append(max(list_p)/10000)
        state_max2.append(state_max)
        print(state_max)
        F[:,t] = np.array(list_max) * np.transpose(emission_probability[:,obs_seq[t]])
    invisible = ['Sunny','Cloud','Rainy']
    besti = getMaxIndex(F[:,Col-1])
    bestinv = []
    bestinv.append(invisible[besti])
    for i in range(Col-2,-1,-1):
        besti = state_max2[i][besti]
        bestinv.append(invisible[besti])
    bestinv = bestinv[::-1]
    print(bestinv)
    return F

if __name__=='__main__':
    #隐藏状态
    invisible=['Sunny','Cloud','Rainy']
    #初始状态
    pi=[0.63,0.17,0.20]
    #转移矩阵
    trainsion_probility=[[0.5,0.375,0.125],[0.25,0.125,0.625],[0.25,0.375,0.375]]
    #发射矩阵
    emission_probility=[[0.6,0.2,0.15,0.05],[0.25,0.25,0.25,0.25],[0.05,0.10,0.35,0.5]]
    #最后显示状态
    obs_seq=[0,1,2,3,3,3,3,3,0,0,2]
    #最后返回一个Row*Col的矩阵结果
    F = viterbi(trainsion_probility, emission_probility, pi, obs_seq)
    print(F)
