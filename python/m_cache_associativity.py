import matplotlib.pyplot as plt
import seaborn as sns
import pandas as pd
import re


def load_file_as_dataframe(input_file):
    with open(input_file, "r") as result:
        content = result.read()
    df = build_data_set_from_text(content)
    return df

def build_data_set_from_text(content):
    df = pd.DataFrame()
    values = re.findall(r"([0-9]+)\s+(.+)", content)
    step = [float(t[0]) for t in values]
    time = [float(t[1]) for t in values]

    df["step"] = step
    df["Run time (ms)"] = time
    return df

def main():
    input_file = "build/m_cache_associativity.txt"
    output_png = "docs/m_cache_associativity.png"

    sns.set_style("dark")
    sns.set_context("talk")

    plt.axvline(128, color="lightgreen", linewidth=3)
    plt.axvline(256, color="lightgreen", linewidth=3)
    plt.axvline(512, color="lightgreen", linewidth=3)
    #plt.axvline(256000, color="orange", linewidth=3)
    #plt.axvline(4000000, color="lightblue", linewidth=3)

    df = load_file_as_dataframe(input_file)
    sns.scatterplot(data=df, x="step", y="Run time (ms)", alpha=0.1)
    df = df.groupby("step").mean()
    sns.lineplot(data=df, x="step", y="Run time (ms)")

    #plt.xscale("log")
    #plt.xticks(
    #    [1000, 32000, 256000, 4000000, 256000000],
    #    ["1k", "32k", "256k", "4M", "256M"])
    plt.ylim([0, 1.15 * df["Run time (ms)"].max()])
    #plt.set_ylim([32,64])
    plt.tight_layout()
    plt.savefig(output_png, dpi=400)
    plt.show()

if __name__ == "__main__":
    main()
