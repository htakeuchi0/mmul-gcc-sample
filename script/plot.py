import json
import os
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

def main():
    # ファイルの読み込み
    filenames = [
        'mmul-O0.json',
        'mmul-O1.json',
        'mmul-O2.json',
        'mmul-O3.json' ]
    loaded_data = []
    for filename in filenames:
        with open(os.path.join('..', 'log', filename)) as f:
            loaded_data.append(json.load(f)[0])

    # ファイルのマージ
    optim_labels = ['-O0', '-O1', '-O2', '-O3']
    eval_data = {}
    for optim_label, data in zip(optim_labels, loaded_data):
        eval_data[optim_label] = data

    # 実行時間の平均値
    # 最適化レベルをレコードインデックスにするために転置する
    eval_data_mean = {
        optim_label: {key:
            np.mean(eval_data[optim_label][key]) for key in eval_data[optim_label]}
                for optim_label in eval_data}
    df = pd.DataFrame(eval_data_mean)
    df = df.T

    # 実行時間の標本標準偏差
    # 最適化レベルをレコードインデックスにするために転置する
    eval_data_std = {
        optim_label: {key:
            np.std(eval_data[optim_label][key]) for key in eval_data[optim_label]}
                for optim_label in eval_data}
    df_std = pd.DataFrame(eval_data_std)
    df_std = df_std.T

    # 表示順を固定するためにラベル順を指定する
    y_labels = [
        'mdim_raw_array',
        'mdim_std_array',
        'mdim_new_array',
        'mdim_vector',
        'sdim_raw_array',
        'sdim_std_array',
        'sdim_new_array',
        'sdim_vector',
        'sdim_raw_array_trans',
        'sdim_std_array_trans',
        'sdim_new_array_trans',
        'sdim_vector_trans' ]

    # 標本標準偏差でエラーバーをつける
    df.plot.bar(
        y=y_labels, figsize=(12, 6), align='center', yerr=df_std)

    # ラベルを設定する
    plt.xlabel('Optimization Level')
    plt.ylabel('Elapsed Time [sec]')

    # x軸表示が回転されているため戻す
    plt.xticks(rotation=0)

    # ファイルに保存
    plt.savefig('plot.png')

if __name__ == '__main__':
    main()

