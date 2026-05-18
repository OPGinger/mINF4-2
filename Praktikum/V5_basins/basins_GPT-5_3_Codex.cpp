#include <array>
#include <complex>
#include <fstream>
#include <iostream>

namespace {

using cplx = std::complex<double>;

constexpr unsigned n_rows = 600;
constexpr unsigned n_cols = 600;
constexpr double t = 2.0;
constexpr unsigned max_iter = 100;
constexpr double eps = 1e-3;

constexpr cplx r1 = cplx(1.0, 0.0);
constexpr cplx r2 = cplx(-0.5, 0.8660254037844386);  // 0.5 * (-1 + i*sqrt(3))
constexpr cplx r3 = cplx(-0.5, -0.8660254037844386); // 0.5 * (-1 - i*sqrt(3))

cplx f(const cplx& z) {
    return (z - r1) * (z - r2) * (z - r3);
}

cplx fp(const cplx& z) {
    return (z - r1) * (z - r2) + (z - r1) * (z - r3) + (z - r2) * (z - r3);
}

cplx newton_step(const cplx& z) {
    const cplx df = fp(z);
    if (std::abs(df) < 1e-12) {
        return z;
    }
    return z - f(z) / df;
}

std::array<unsigned, 3> classify_pixel(const cplx& z0) {
    cplx z = z0;

    for (unsigned k = 1; k <= max_iter; ++k) {
        z = newton_step(z);

        if (std::abs(z - r1) < eps) {
            return {255, 0, 0};
        }
        if (std::abs(z - r2) < eps) {
            return {0, 255, 0};
        }
        if (std::abs(z - r3) < eps) {
            return {0, 0, 255};
        }
    }

    return {255, 255, 255};
}

} // namespace

int main() {
    std::ofstream out("basins.ppm");
    if (!out) {
        std::cerr << "Kann basins.ppm nicht schreiben.\n";
        return 1;
    }

    out << "P3\n";
    out << n_cols << ' ' << n_rows << "\n255\n";

    const double x_min = -t;
    const double x_max = t;
    const double y_min = -t;
    const double y_max = t;

    const double rx = (x_max - x_min) / (n_cols - 1.0);
    const double ry = (y_max - y_min) / (n_rows - 1.0);

    for (unsigned row = 0; row < n_rows; ++row) {
        const double y = y_min + row * ry;
        for (unsigned col = 0; col < n_cols; ++col) {
            const double x = x_min + col * rx;
            const auto rgb = classify_pixel(cplx(x, y));
            out << rgb[0] << ' ' << rgb[1] << ' ' << rgb[2] << '\n';
        }
    }

    std::cout << "Bild geschrieben: basins.ppm (" << n_cols << "x" << n_rows << ")\n";
    return 0;
}
