#include "CppUnitTest.h"
extern "C" {
#include "dealerAI.h"
}

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DealerAITesting
{
	TEST_CLASS(DealerAITests)
	{
	public:
		TEST_METHOD(REQ_DLR_006)
		{
			int lives[2] = { 2,2 };
			DIFFICULTY diff = DIF_EASY;
			ITEM_T items[2][ITEMS_CAP];

			for (int i = 0; i < ITEMS_CAP; i++) {
				items[PLAYER][i] = EMPTY;
				items[DEALER][i] = EMPTY;
			}
			items[DEALER][0] = BEER;
			items[DEALER][1] = MAGNIFYING_GLASS;
			items[DEALER][2] = CIGARETTE_PACK;
			items[DEALER][3] = HANDCUFFS;
			items[DEALER][4] = HAND_SAW;
			items[DEALER][5] = HANDCUFFS;
			items[DEALER][6] = HAND_SAW;
			items[DEALER][7] = MAGNIFYING_GLASS;
			BulletsLink bullets = NULL;
			for (int i = 0; i < 3; i++) {
				addBullet(&bullets, LIVE);
			}
			bool oppHandcuffed = false;
			
			bool actual = dealerTurn(lives, &bullets, items, &oppHandcuffed, diff);
			for (int i = 0; i < 5; i++) {
				Assert::IsTrue(items[DEALER][i] == (ITEM_T)EMPTY);
			}
			for (int i = 5; i < ITEMS_CAP; i++) {
				Assert::IsTrue(items[DEALER][i] != (ITEM_T)EMPTY);
			}

			clearBullets(&bullets);
		}
		TEST_METHOD(REQ_DLR_007)
		{
			int lives[2] = { 5,5 };
			DIFFICULTY diff = DIF_EASY;
			ITEM_T items[2][ITEMS_CAP];

			for (int i = 0; i < ITEMS_CAP; i++) {
				items[PLAYER][i] = EMPTY;
				items[DEALER][i] = EMPTY;
			}
			BulletsLink bullets = NULL;
			addBullet(&bullets, LIVE);
			bool oppHandcuffed = false;

			bool actual = dealerTurn(lives, &bullets, items, &oppHandcuffed, diff);
			Assert::IsTrue(lives[PLAYER] == 4);
			Assert::IsTrue(lives[DEALER] == 5);
			Assert::IsTrue(bulletCount(bullets) == 0);

			clearBullets(&bullets);
		}
		
	};
}
