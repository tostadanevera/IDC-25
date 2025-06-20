#include "unity.h"
#include "core/AccessController.h"
#include "unity_config.h"
#include "mocks/MockDatabase.h"
#include "mocks/MockNotifier.h"
#include "mocks/MockOutput.h"
#include <string>
using std::string;

void setUp(void) {}
void tearDown(void) {}

class AccessControllerTest {
public:
    MockDatabase db;
    MockNotifier notifier;
    MockOutput output;
    AccessController controller{db, notifier, output};
    
    void SetUp() {
        // Configurar datos de prueba
        db.setTestData("AUTH123", true);
        db.setTestData("UNAUTH456", false);
        
        // Resetear mocks
        notifier.reset();
        output.reset();
    }
};

void test_authorized_card_grants_access() {
    AccessControllerTest fixture;
    
    std::string uid = "AUTH123";

    // Act
    bool result = fixture.controller.onCardRead(uid);
    
    // Assert
    TEST_ASSERT_TRUE(result);
    TEST_ASSERT_EQUAL_STRING("GRANTED: AUTH123", fixture.notifier.getLastNotification().c_str());
    TEST_ASSERT_EQUAL_STRING("GRANTED", fixture.output.getLastAction().c_str());
}

void test_unauthorized_card_denies_access() {
    AccessControllerTest fixture;
    
    std::string uid = "UNAUTH456";

    // Act
    bool result = fixture.controller.onCardRead(uid);
    
    // Assert
    TEST_ASSERT_FALSE(result);
    TEST_ASSERT_EQUAL_STRING("DENIED: UNAUTH456", fixture.notifier.getLastNotification().c_str());
    TEST_ASSERT_EQUAL_STRING("DENIED", fixture.output.getLastAction().c_str());
}

void test_card_registration() {
    AccessControllerTest fixture;
    
    std::string uid = "NEWCARD999";

    // Act
    bool result = fixture.controller.registerCard(uid);
    
    // Assert
    TEST_ASSERT_TRUE(result);
    TEST_ASSERT_TRUE(fixture.db.isAuthorized(uid));
}

int main() {
    UNITY_BEGIN();
    
    RUN_TEST(test_authorized_card_grants_access);
    RUN_TEST(test_unauthorized_card_denies_access);
    RUN_TEST(test_card_registration);
    
    return UNITY_END();
}