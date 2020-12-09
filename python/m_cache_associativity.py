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

    plt.figure(figsize=(15,7))

    sns.set_style("dark")
    sns.set_context("talk")

   
    # plt.axvline(256000, color="orange", linewidth=3)
    # plt.axvline(4000000, color="lightblue", linewidth=3)

    df = load_file_as_dataframe(input_file)
    sns.scatterplot(data=df, x="step", y="Run time (ms)", alpha=0.2, s=20, color="lightblue")


    df = df.groupby("step").mean()
    sns.scatterplot(data=df, x="step", y="Run time (ms)", alpha=0.8, s=80, color="darkblue")

    peculiar_values_label = ["128*"+str(i) for i in range (1, 16)]
    peculiar_values = [eval(i) for i in peculiar_values_label]
    for v_ind,v in enumerate(peculiar_values):
        plt.axvline(v, color="darkgrey", linewidth=1)
        plt.text(1.01*v,0.05*df["Run time (ms)"].max(),peculiar_values_label[v_ind],rotation=90)

    plt.xscale("log")
    plt.xticks(
        [pow(2,i) for i in range(7,12)],[pow(2,i) for i in range(7,12)]
    )
    plt.xlim([200,2200])
    plt.ylim([0, 1.1 * df["Run time (ms)"].max()])
    plt.tight_layout()
    plt.savefig(output_png, dpi=90)
    plt.show()


if __name__ == "__main__":
    main()
