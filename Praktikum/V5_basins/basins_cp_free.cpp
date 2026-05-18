#include <complex>
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>
#include <cmath>

int main()
{
    using std::complex;
    constexpr unsigned n_row = 400;  // y
    constexpr unsigned n_col = 400;  // x
    // complex plane bounds (t = 2.0)
    constexpr double t = 2.0;
    constexpr double x_min = -t;
    constexpr double x_max = +t;
    constexpr double y_min = -t;
    constexpr double y_max = +t;
    constexpr double Rx = (x_max - x_min) / ( n_col - 0.0 );
    constexpr double Ry = (y_max - y_min) / ( n_row - 0.0 );

    const unsigned width = n_col;
    const unsigned height = n_row;

    const int max_iter = 100;
    const double eps = 1e-3;

    // roots: third roots of unity as example
    const complex<double> r1{1.0, 0.0};
    const complex<double> r2{-0.5,  std::sqrt(3.0)/2.0};
    const complex<double> r3{-0.5, -std::sqrt(3.0)/2.0};

    std::vector<uint8_t> img;
    img.resize(width * height * 3);

    for (unsigned row = 0; row < n_row; ++row)
    {
        const double y = y_min + (row - 0) * Ry;
        for (unsigned col = 0; col < n_col; ++col)
        {
            const double x = x_min + (col - 0) * Rx;
            complex<double> z{x, y};

            int root = -1;

            complex<double> zn = z;
            for (int k = 0; k < max_iter; ++k)
            {
                // compute f and f'
                const complex<double> a = (zn - r1);
                const complex<double> b = (zn - r2);
                const complex<double> c = (zn - r3);
                const complex<double> f = a * b * c;
                const complex<double> fp = a*b + a*c + b*c; // f'(z)

                // avoid division by zero
                if (std::abs(fp) == 0.0) break;

                // Newton iteration N(z) = z - f/f'
                zn = zn - f / fp;

                if (std::abs(zn - r1) < eps) { root = 1; break; }
                if (std::abs(zn - r2) < eps) { root = 2; break; }
                if (std::abs(zn - r3) < eps) { root = 3; break; }
            }

            size_t idx = (row * width + col) * 3;
            if (root == 1)
            {
                img[idx+0] = 255; img[idx+1] = 0;   img[idx+2] = 0;   // red
            }
            else if (root == 2)
            {
                img[idx+0] = 0;   img[idx+1] = 255; img[idx+2] = 0;   // green
            }
            else if (root == 3)
            {
                img[idx+0] = 0;   img[idx+1] = 0;   img[idx+2] = 255; // blue
            }
            else
            {
                img[idx+0] = 255; img[idx+1] = 255; img[idx+2] = 255; // white
            }
        }
    }

    // write PPM (binary P6)
    std::ofstream ofs("basins.ppm", std::ios::binary);
    if (!ofs)
    {
        std::cerr << "Failed to open output file basins.ppm\n";
        return 1;
    }
    ofs << "P6\n" << width << " " << height << "\n255\n";
    ofs.write(reinterpret_cast<const char*>(img.data()), img.size());
    ofs.close();

    std::cout << "Wrote basins.ppm (" << width << "x" << height << ")\n";
    return 0;
}
