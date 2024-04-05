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
			int lives[2] = { 5,5 };
			DIFFICULTY diff = DIF_EASY;
			ITEM** items = (ITEM**)malloc(2 * sizeof(int*));
			if (items == NULL) {
				Assert::Fail();
			}
			for (int i = 0; i < 2; i++) {
				items[i] = (ITEM*)malloc(ITEMS_CAP * sizeof(int));
				if (items[i] == NULL) {
					Assert::Fail();
				}
			}

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
				Assert::IsTrue(items[DEALER][i] == EMPTY);
			}
			for (int i = 5; i < ITEMS_CAP; i++) {
				Assert::IsTrue(items[DEALER][i] != EMPTY);
			}

			for (int i = 0; i < 2; i++) {
				free(items[i]);
			}
			free(items);
			clearBullets(&bullets);
		}
		
	};
}
