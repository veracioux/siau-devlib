#include "valuespec.h"
#include <QtTest/QtTest>

class TestValueSpec : public QObject
{
    Q_OBJECT

    using VS = ValueSpec;
private slots:

    void testIsValidType()
    {
        QVERIFY(VS::isValidType("void") == true);
        QVERIFY(VS::isValidType("a") == true);
        QVERIFY(VS::isValidType("A1") == true);
        QVERIFY(VS::isValidType("a_b") == true);
        QVERIFY(VS::isValidType("a_B3") == true);
        QVERIFY(VS::isValidType("_a_b_6") == true);
        QVERIFY(VS::isValidType("1") == false);
        QVERIFY(VS::isValidType("") == false);
        QVERIFY(VS::isValidType("1abc") == false);
        QVERIFY(VS::isValidType("1a_b") == false);
    }

    void testIsValidSpecBool()
    {
        QVERIFY(VS::isValidSpec("bool", {}) == true);
        QVERIFY(VS::isValidSpec("bool", { "" }) == false);
        QVERIFY(VS::isValidSpec("bool", { "true", "false" }) == false);
        QVERIFY(VS::isValidSpec("bool", { "", "" }) == false);
    }

    void testIsValidSpecCustomEnum()
    {
        QVERIFY(VS::isValidSpec("MyEnum", { "a" }) == true);
        QVERIFY(VS::isValidSpec("MyEnum", { "a", "b" }) == true);
        QVERIFY(VS::isValidSpec("MyEnum", { "ab", "C", "x1" }) == true);
        QVERIFY(VS::isValidSpec("MyEnum", { "_ab" }) == true);
        QVERIFY(VS::isValidSpec("My_Enum2", { "_ab" }) == true);
        QVERIFY(VS::isValidSpec("MyEnum", {}) == false);
        QVERIFY(VS::isValidSpec("MyEnum", { "" }) == false);
        QVERIFY(VS::isValidSpec("MyEnum", { "", "" }) == false);
        QVERIFY(VS::isValidSpec("MyEnum", { "", "ab" }) == false);
        QVERIFY(VS::isValidSpec("1MyEnum", { "a" }) == false);
    }

    void testIsValidSpecFloat()
    {
        QVERIFY(VS::isValidSpec("float", {}) == true);
        QVERIFY(VS::isValidSpec("float", { "1.1", "2.2" }) == true);
        QVERIFY(VS::isValidSpec("float", { "1", "2" }) == true);
        QVERIFY(VS::isValidSpec("float", { "" }) == false);
        QVERIFY(VS::isValidSpec("float", { "1" }) == false);
        QVERIFY(VS::isValidSpec("float", { "1", "2", "3" }) == false);
    }

    void testIsValidSpecInt()
    {
        QVERIFY(VS::isValidSpec("int", {}) == true);
        QVERIFY(VS::isValidSpec("int", { "1", "2" }) == true);
        QVERIFY(VS::isValidSpec("int", { "" }) == false);
        QVERIFY(VS::isValidSpec("int", { "1" }) == false);
        QVERIFY(VS::isValidSpec("int", { "1.2", "2.2" }) == false);
        QVERIFY(VS::isValidSpec("int", { "1", "2", "3" }) == false);
    }

    void testIsValidSpecVoid()
    {
        QVERIFY(VS::isValidSpec("void", {}) == true);
        QVERIFY(VS::isValidSpec("void", { "" }) == false);
        QVERIFY(VS::isValidSpec("void", { "a", "b" }) == false);
    }

    void testDefaultConstructor()
    {
        ValueSpec spec;
        QVERIFY(spec.isVoid());
        QVERIFY(!spec.isBool());
        QVERIFY(!spec.isCustomEnum());
        QVERIFY(!spec.isFloat());
        QVERIFY(!spec.isInt());
        QVERIFY(spec.getValueRange().isEmpty());
    }

    void testOtherConstructor()
    {
        QVERIFY(ValueSpec("bool", {}).isBool());
        QVERIFY(ValueSpec("float", {}).isFloat());
        QVERIFY(ValueSpec("MyEnum", { "a" }).isCustomEnum());
        QVERIFY(ValueSpec("int", {}).isInt());
        QVERIFY(ValueSpec("void", {}).isVoid());

        ValueSpec spec = ValueSpec("int", { "1", "2" });
        QCOMPARE(spec.getMinInt(), 1);
        QCOMPARE(spec.getMaxInt(), 2);
        spec = ValueSpec("float", { "-0.5", "2.3" });
        QCOMPARE(spec.getMinFloat(), -0.5f);
        QCOMPARE(spec.getMaxFloat(), 2.3f);

        spec = ValueSpec("float", {});
        QVERIFY(qIsNaN(spec.getMinFloat()));
        QVERIFY(qIsNaN(spec.getMaxFloat()));
    }

    void testSetters()
    {
        ValueSpec spec("int", {});
        QVERIFY_EXCEPTION_THROWN(spec.setValueRange({ "0" }),
                                 std::domain_error);
        try {
            spec.setValueRange({ "1", "2" });
            spec.setValueType("float");
            spec.setUnit("%");
            spec.setValueRange({ "1.2", "3.8" });
            // Type changed to int but value range is a pair of floats
            QVERIFY_EXCEPTION_THROWN(spec.setValueType("int"),
                                     std::domain_error);
            QVERIFY_EXCEPTION_THROWN(spec.setValueType("void"),
                                     std::domain_error);
        } catch (std::exception& e) {
            QFAIL("Exception thrown");
        }
    }
};

QTEST_MAIN(TestValueSpec)
#include "valuespec.moc"
