import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

def main():
    # 各方式の平均値をまとめたファイルを読み込む
    df = pd.read_csv('eval-2.csv', index_col=0)
    df.T.plot.bar()

    # ラベルを設定する
    plt.xlabel('Optimization Level')
    plt.ylabel('Elapsed Time [sec]')
    plt.ylim([0, 0.1])

    # x軸表示が回転されているため戻す
    plt.xticks(rotation=0)

    # ファイルに保存
    plt.savefig('plot-2.png')

if __name__ == '__main__':
    main()
