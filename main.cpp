#include "week00/CrossRiver.h"
#include "week01/SheepDistribution.h"

int main() {
//    /**
//     * week00 CrossRiver
//     */
//    auto test_week00 = CrossRiver(3, 2);
//    test_week00.run();


    /**
     * week01 SheepDistribution
     */
    std::ofstream out("../output.txt", std::ios_base::out);
    auto test_week01 = SheepDistribution(2, 4);
    test_week01.calculate(std::cout);
    test_week01.calculate(out);

    return 0;
}
