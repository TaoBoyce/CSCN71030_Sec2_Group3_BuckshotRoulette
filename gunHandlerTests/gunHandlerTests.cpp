#include "CppUnitTest.h"
extern "C" {
#include "bulletsHandler.h"
#include "gunHandler.h"
}


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace gunHandlerTests
{
	TEST_CLASS(gunHandlerTests)
	{
	public:
#pragma region REQ_GUN_005 RETURN
		TEST_METHOD(REQ_GUN_005_1)
		{
			//return true if opponent turn is skipped
			//shoot self when live
			BulletsLink bLink = (BulletsLink)malloc(sizeof(BulletsNode));
			if (bLink == NULL) {
				Assert::Fail();
			}
			bLink->bullet = LIVE;
			bLink->next = NULL;
			int lives = 5;
			bool expected = false;
			bool actual = shootGun(&lives, &bLink, true, false);

			free(bLink);

			Assert::AreEqual(expected, actual);
		}
		TEST_METHOD(REQ_GUN_005_2)
		{
			//return true if opponent turn is skipped
			//shoot self when blank
			BulletsLink bLink = (BulletsLink)malloc(sizeof(BulletsNode));
			if (bLink == NULL) {
				Assert::Fail();
			}
			bLink->bullet = BLANK;
			bLink->next = NULL;
			int lives = 5;
			bool expected = true;
			bool actual = shootGun(&lives, &bLink, true, false);

			free(bLink);

			Assert::AreEqual(expected, actual);
		}
		TEST_METHOD(REQ_GUN_005_3)
		{
			//return true if opponent turn is skipped
			//shoot opponent when live
			BulletsLink bLink = (BulletsLink)malloc(sizeof(BulletsNode));
			if (bLink == NULL) {
				Assert::Fail();
			}
			bLink->bullet = LIVE;
			bLink->next = NULL;
			int lives = 5;
			bool expected = false;
			bool actual = shootGun(&lives, &bLink, false, false);

			free(bLink);

			Assert::AreEqual(expected, actual);
		}
		TEST_METHOD(REQ_GUN_005_4)
		{
			//return true if opponent turn is skipped
			//shoot opponent when blank
			BulletsLink bLink = (BulletsLink)malloc(sizeof(BulletsNode));
			if (bLink == NULL) {
				Assert::Fail();
			}
			bLink->bullet = BLANK;
			bLink->next = NULL;
			int lives = 5;
			bool expected = false;
			bool actual = shootGun(&lives, &bLink, false, false);

			free(bLink);

			Assert::AreEqual(expected, actual);
		}
#pragma endregion
#pragma region REQ_GUN_006_A LIVES
		TEST_METHOD(REQ_GUN_006_A_1)
		{
			//change life depending on result
			//shoot self when live
			BulletsLink bLink = (BulletsLink)malloc(sizeof(BulletsNode));
			if (bLink == NULL) {
				Assert::Fail();
			}
			bLink->bullet = LIVE;
			bLink->next = NULL;
			int lives = 5;
			int expected = lives - 1;
			shootGun(&lives, &bLink, true, false);

			free(bLink);

			Assert::AreEqual(expected, lives);
		}
		TEST_METHOD(REQ_GUN_006_A_2)
		{
			//change life depending on result
			//shoot self when blank
			BulletsLink bLink = (BulletsLink)malloc(sizeof(BulletsNode));
			if (bLink == NULL) {
				Assert::Fail();
			}
			bLink->bullet = BLANK;
			bLink->next = NULL;
			int lives = 5;
			int expected = lives;
			shootGun(&lives, &bLink, true, false);

			free(bLink);

			Assert::AreEqual(expected, lives);
		}
		TEST_METHOD(REQ_GUN_006_A_3)
		{
			//change life depending on result
			//shoot opponent when live
			BulletsLink bLink = (BulletsLink)malloc(sizeof(BulletsNode));
			if (bLink == NULL) {
				Assert::Fail();
			}
			bLink->bullet = LIVE;
			bLink->next = NULL;
			int lives = 5;
			int expected = lives - 1;
			shootGun(&lives, &bLink, false, false);

			free(bLink);

			Assert::AreEqual(expected, lives);
		}
		TEST_METHOD(REQ_GUN_006_A_4)
		{
			//change life depending on result
			//shoot opponent when blank
			BulletsLink bLink = (BulletsLink)malloc(sizeof(BulletsNode));
			if (bLink == NULL) {
				Assert::Fail();
			}
			bLink->bullet = BLANK;
			bLink->next = NULL;
			int lives = 5;
			int expected = lives;
			shootGun(&lives, &bLink, false, false);

			free(bLink);

			Assert::AreEqual(expected, lives);
		}
#pragma endregion 
#pragma region REQ_GUN_006_B LIVES DOUBLE DAMAGE
		TEST_METHOD(REQ_GUN_006_B_1)
		{
			//change life depending on result
			//shoot self when live and double damage
			BulletsLink bLink = (BulletsLink)malloc(sizeof(BulletsNode));
			if (bLink == NULL) {
				Assert::Fail();
			}
			bLink->bullet = LIVE;
			bLink->next = NULL;
			int lives = 5;
			int expected = lives - 2;
			shootGun(&lives, &bLink, true, true);

			free(bLink);

			Assert::AreEqual(expected, lives);
		}
		TEST_METHOD(REQ_GUN_006_B_2)
		{
			//change life depending on result
			//shoot self when blank and double damage
			BulletsLink bLink = (BulletsLink)malloc(sizeof(BulletsNode));
			if (bLink == NULL) {
				Assert::Fail();
			}
			bLink->bullet = BLANK;
			bLink->next = NULL;
			int lives = 5;
			int expected = lives;
			shootGun(&lives, &bLink, true, true);

			free(bLink);

			Assert::AreEqual(expected, lives);
		}
		TEST_METHOD(REQ_GUN_006_B_3)
		{
			//change life depending on result
			//shoot opponent when live and double damage
			BulletsLink bLink = (BulletsLink)malloc(sizeof(BulletsNode));
			if (bLink == NULL) {
				Assert::Fail();
			}
			bLink->bullet = LIVE;
			bLink->next = NULL;
			int lives = 5;
			int expected = lives - 2;
			shootGun(&lives, &bLink, false, true);

			free(bLink);

			Assert::AreEqual(expected, lives);
		}
		TEST_METHOD(REQ_GUN_006_B_4)
		{
			//change life depending on result
			//shoot opponent when blank and double damage
			BulletsLink bLink = (BulletsLink)malloc(sizeof(BulletsNode));
			if (bLink == NULL) {
				Assert::Fail();
			}
			bLink->bullet = BLANK;
			bLink->next = NULL;
			int lives = 5;
			int expected = lives;
			shootGun(&lives, &bLink, false, true);

			free(bLink);

			Assert::AreEqual(expected, lives);
		}
#pragma endregion

	};
}
