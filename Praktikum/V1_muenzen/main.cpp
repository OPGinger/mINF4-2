#include <cstdint>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

static void generateRecursive(
	int n,
	int pos,
	int run,
	std::vector<char>& pattern,
	std::vector<int>& comp,
	std::uint64_t& idx,
	int idxWidth,
	std::ostringstream& output) {
	if (pos == n - 1) {
		comp.push_back(run);
		std::string patternStr(pattern.begin(), pattern.end());
		output << std::setw(idxWidth) << idx << ":  "
			   << std::setw(n - 1) << patternStr << "  [ ";
		for (std::size_t i = 0; i < comp.size(); ++i) {
			if (i > 0) {
				output << ' ';
			}
			output << comp[i];
		}
		output << " ]\n";
		++idx;
		comp.pop_back();
		return;
	}

	pattern[static_cast<std::size_t>(pos)] = '.';
	comp.push_back(run);
	generateRecursive(n, pos + 1, 1, pattern, comp, idx, idxWidth, output);
	comp.pop_back();

	pattern[static_cast<std::size_t>(pos)] = '1';
	generateRecursive(n, pos + 1, run + 1, pattern, comp, idx, idxWidth, output);
}

int main(int argc, char** argv) {
	constexpr int MAX_N = 63;
	int n = 0;

	std::ostringstream output;

	if (argc != 2) {
		return 1;
	}

	{
		std::istringstream is(argv[1]);
		if (!(is >> n) || !is.eof() || n < 0 || n > MAX_N) {
			return 1;
		}
	}

	std::uint64_t count = (n == 0) ? 1ULL : (1ULL << (n - 1));

	int idxWidth = static_cast<int>(std::to_string(count - 1).size());
	if (n == 0) {
		output << std::setw(idxWidth) << 0 << ":  "
			   << std::setw(0) << "" << "  [ ]\n";
	} else {
		std::vector<int> comp;
		comp.reserve(static_cast<std::size_t>(n));
		std::vector<char> pattern(static_cast<std::size_t>(n - 1), '.');
		std::uint64_t idx = 0;
		generateRecursive(n, 0, 1, pattern, comp, idx, idxWidth, output);
	}
	output << "ct=" << count << "\n";

	std::cout << output.str();

	return 0;
}
