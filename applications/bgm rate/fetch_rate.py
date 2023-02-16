# -*- coding: utf-8 -*-
import requests
import json
import taglib
import os
import time


bangumi_ids = [
    362479,361095,315744,351375,
    344874,345980,270739,236657,361110,317613,353605,
    302286,381842,348335,337459,
    364468,364845,375817,389450,
    316131,364450,342200,368816,
    343106,322130,371546,327606,
    371396,366793,298477,203526,
    243981,326895,356774,354414,
    328609,208908,349441,272510,
    271151,270739,287488,315574,
    239816,240562,248154,
    296659,335579,306742,354146,
    27364,306429,193562,147568,
    120925,38040,192794,80864,
    110600,93545,252655,174043,
    233926,373710,183878,282372,
    10440,378862,395714,374206,
    374319,268545,293049,274646,
    296151,320851,174138,328609,
    208908,150775
]

bangumi_collection = {
    1: [],
    2: [],
    3: [],
    4: [],
    5: []
}

#6.37 0.00 28.12 67.19 4.69 1.83 17.68 75.00 4.27 1.83 21.00 73.06 3.20

def output_rating(rating):
    # print(rating)
    total=rating["total"]
    count_low,count_mid,count_high,count_ultra_high=0,0,0,0
    for i in range(1,4):
        count_low+=rating["count"][str(i)]
    for i in range(5,7):
        count_mid+=rating["count"][str(i)]
    for i in range(7,9):
        count_high+=rating["count"][str(i)]
    for i in range(9,11):
        count_ultra_high+=rating["count"][str(i)]
    print('%.2f' % (float(count_low*100)/float(total)),end=" ")
    print('%.2f' % (float(count_mid*100)/float(total)),end=" ")
    print('%.2f' % (float(count_high*100)/float(total)),end=" ")
    print('%.2f' % (float(count_ultra_high*100)/float(total)),end=" ")

def output_day(day):
    # print(day)
    output_rating(day["rating"])
    print(day["collect"]["doing"],end=" ")

def print_data(bgm_id):
    r = requests.get('https://api.netaba.re/archive/'+bgm_id)
    r = json.loads(r.text)
    air_date=r["subject"]["air_date"]
    # air_date="2018-10-05"
    history=r["history"]
    print(history[0]["score"],end=" ")
    air_data_id=0
    for i in range(0,len(history)):
        day=history[i]
        if (air_date in day["recordedAt"]):
            air_data_id=i
            break
    output_day(history[air_data_id-1])
    output_day(history[air_data_id-11])
    output_day(history[air_data_id-21])
    # output_day(history[air_data_id-1])
    # output_day(history[air_data_id-11])
    # output_day(history[air_data_id-21])
    print("")

if __name__=="__main__":
    print(len(bangumi_ids))
    my_input=input().split(" ")
    for i in range(0,len(my_input)):
        bangumi_collection[int(my_input[i])].append(bangumi_ids[i])
    
    for i in range(1,6):
        for id in bangumi_collection[i]:
            print(id," ")
        print("")
    # for id in bangumi_ids:
    #     while True:
    #         try:
    #             print_data(str(id))
    #             # sleep 1 second
    #             time.sleep(1)
    #             break
    #         except:
    #             print("error")
    #             time.sleep(1)
    #             continue
    # while True:
    #     id=input()
    #     if (id==-1):
    #         break
    #     print_data(str(id))

