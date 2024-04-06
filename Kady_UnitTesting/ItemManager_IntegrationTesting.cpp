#include "CppUnitTest.h"
extern "C" {
#include "dealerAI.h"
#include "itemsHandler.h"
#include "gunHandler.h"
}

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ItemHandlerTesting
{
	TEST_CLASS(ItemHandlerTests)
	{
	public:
		TEST_METHOD(ITM007) {
			int lives[2] = { 2, 2 };
			BulletsLink bullets;
			addBullet(&bullets, LIVE);
			ITEM_T items[2][ITEMS_CAP] = { {HANDCUFFS, MAGNIFYING_GLASS}, {BEER, BEER} };

			if (item_remove(items[PLAYER], 0) == HANDCUFFS) {
				return;
			}
			else {
				bool cuffed = false;
				dealerTurn(lives, &bullets, items, &cuffed, DIF_EASY);
				Assert::Fail();
			}
		}
		TEST_METHOD(ITM008) {
			ITEM_T items[2] = { HAND_SAW, BEER };
			int lives[2] = { 2, 2 };
			BulletsLink bullets;
			addBullet(&bullets, LIVE);
			addBullet(&bullets, BLANK);
			
			if (item_remove(items, 0) == HAND_SAW) {
				shootGun(lives, &bullets, false, true);
			}
			else {
				shootGun(lives, &bullets, false, false);
				Assert::Fail();
			}
		}
		TEST_METHOD(ITM009) {
			ITEM_T items[2] = { MAGNIFYING_GLASS, EMPTY };
			BulletsLink bullets;
			addBullet(&bullets, LIVE);
			addBullet(&bullets, BLANK);
			if (item_remove(items, 0) == MAGNIFYING_GLASS) {
				if (peekBullet(bullets) != BLANK) {
					Assert::Fail();
				}
			}
			else {
				Assert::Fail();
			}

		}

		
	};
}
