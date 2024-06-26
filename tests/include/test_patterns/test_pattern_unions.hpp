#pragma once

#include "test_pattern.hpp"

#include <pl/patterns/pattern_unsigned.hpp>
#include <pl/patterns/pattern_signed.hpp>
#include <pl/patterns/pattern_array_static.hpp>
#include <pl/patterns/pattern_union.hpp>

namespace pl::test {

    class TestPatternUnions : public TestPattern {
    public:
        TestPatternUnions() : TestPattern("Unions") {
            auto testUnion = create<PatternUnion>("TestUnion", "testUnion", 0x200, sizeof(u64), 0);

            auto array = create<PatternArrayStatic>("s32", "array", 0x200, sizeof(i32[2]), 0);
            array->setEntries(create<PatternSigned>("s32", "", 0x200, sizeof(i32), 0), 2);
            auto variable = create<PatternUnsigned>("u64", "variable", 0x200, sizeof(u64), 0);

            std::vector<std::shared_ptr<Pattern>> unionMembers;
            {
                unionMembers.push_back(std::move(array));
                unionMembers.push_back(std::move(variable));
            }

            testUnion->setMembers(std::move(unionMembers));

            addPattern(std::move(testUnion));
        }
        ~TestPatternUnions() override = default;

        [[nodiscard]] std::string getSourceCode() const override {
            return R"(
                union TestUnion {
                    s32 array[2];
                    u64 variable;
                };

                TestUnion testUnion @ 0x200;
            )";
        }
    };

}