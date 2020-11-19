import matplotlib.pyplot as plt
import seaborn as sns
import pandas as pd
import re

def build_data_set(content, types=["char","short","int","double"]):
    df = pd.DataFrame()
    for t in types:
        print(t)
        values = re.findall(rf"Touching every (.+) index on type {t} (.+) \(ms\)", content)
        x = [float(t[0]) for t in values]
        y = [float(t[1]) for t in values]
        df[t] = y
        df["step"] = x

    return df

def main():
    input_file="build/m_cache_lines.txt"
    output_img="doc/m_cache_lines.png"


    with open(input_file,'r') as result:
        content = result.read()
    
    df = build_data_set(content)

    plt.axvline(16,color='blue')
    plt.axvline(32,color='orange')
    plt.axvline(64,color='green')
    plt.axvline(128,color='red')

    plt.scatter(df["step"], df["double"],c='blue',  label='double (sizeof 8)',s=6.0,alpha=0.5)
    plt.scatter(df["step"], df["int"],c='orange',   label='int    (sizeof 4)',s=6.0,alpha=0.5)
    plt.scatter(df["step"], df["short"],c='green',  label='short  (sizeof 2)',s=6.0,alpha=0.5)
    plt.scatter(df["step"], df["char"],c='red',     label='char   (sizeof 1)',s=6.0,alpha=0.5)

    plt.title('Example Plot')
    plt.ylabel('Run time in ms')
    plt.xlabel('Spacing between accessed elements (delta)')

    plt.legend()

    plt.xscale('symlog')
    plt.xticks([0,1,2,4,8,16,32,64,128,256,512], [0,1,2,4,8,16,32,64,128,256,512])
    plt.xlim([-0.5,513])
    plt.ylim([0,16])
    plt.savefig(output_img, dpi=400)






main()