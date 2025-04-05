#include <mkl.h>
#include <iostream>

int main() {
    // 行列 A (3x3 対称行列), CSR形式
    MKL_INT n = 3;
    MKL_INT ia[4] = {1, 4, 6, 8};          // 行ポインタ
    MKL_INT ja[7] = {1, 2, 3, 1, 3, 1, 2}; // 列インデックス
    double a[7] = {2.0, -1.0, 0.0, -1.0, 2.0, 0.0, -1.0}; // 非ゼロ成分

    double b[3] = {1.0, 0.0, 1.0};  // 右辺
    double x[3];                    // 解ベクトル

    void* pt[64] = {0};
    MKL_INT iparm[64] = {0};
    iparm[0] = 1; // ユーザーが iparm を設定
    iparm[1] = 2; // 並列で実行
    MKL_INT mtype = -2; // 実対称疎行列
    MKL_INT maxfct = 1, mnum = 1, phase = 13, msglvl = 0, error = 0;

    pardiso(pt, &maxfct, &mnum, &mtype, &phase,
            &n, a, ia, ja, nullptr, &n, iparm,
            &msglvl, b, x, &error);

    if (error == 0) {
        std::cout << "Solution x: ";
        for (int i = 0; i < n; ++i) std::cout << x[i] << " ";
        std::cout << std::endl;
    } else {
        std::cout << "PARDISO error: " << error << std::endl;
    }

    return 0;
}
