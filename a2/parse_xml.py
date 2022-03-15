#!/usr/bin/env python3
"""
Created on Mon Feb 28 10:16:43 2022
@author: rivera
#!/usr/bin/env python3
"""

import re


def main():
    # define the collections to be used
    broadcasters_list = []
    filtered_lines = []
    # read the file line by line
    with open('broadcasters.xml') as file:
        for line in file:
            # use regular expressions to collect relevant data
            line = re.findall(r'<(.*?)>(.*?)</\1>', line)
    #         # only include tags with information
            if len(line) > 0:
                filtered_lines.append(line[0])
    broadcaster_dic = {}
    # create the dictionaries
    for i in range(len(filtered_lines)):
        tup = filtered_lines[i]
        broadcaster_dic[tup[0]] = tup[1]
        # separate the information for each broadcaster
        if (i+1)%3 == 0 and i>0:
            broadcasters_list.append(broadcaster_dic)
            broadcaster_dic = {}
    # print the list of dictionaries
    print(broadcasters_list)




if __name__ == '__main__':
   main()


