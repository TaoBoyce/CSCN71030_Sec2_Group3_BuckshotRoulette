#include "CppUnitTest.h"
extern "C" {
#include "dealerAI.h"
#include "itemsHandler.h"
#include "gunHandler.h"
#include "saveload.h"
}

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SaveLoadTesting
{
	TEST_CLASS(SaveLoadTests)
	{
	public:
		TEST_METHOD(SAV006) {
			int lives[2] = { 2, 2 };
			GAME_SAVE *save = create_save();
			ITEM_T items[4] = { BEER, MAGNIFYING_GLASS, BEER, CIGARETTE_PACK };
			BulletsLink b = (BulletsLink)malloc(sizeof(BulletsLink));
			if (b == 0)
				Assert::Fail();
			b->next = 0;
			b->bullet = LIVE;

			update_save(save, 0, 0, lives, items, 4, b, true, true);
			output_save(save);
			destroy_save(save);
			save = create_save();
			
			input_save(save);

			for (int i = 0; i < 3; i++) {
				if (items[i] != save->items[i])
					Assert::Fail();
			}
			destroy_save(save);
		}
		TEST_METHOD(SAV007) {
			int lives[2] = { 2, 2 };
			GAME_SAVE *save = create_save();
			ITEM_T items[4] = { BEER, MAGNIFYING_GLASS, BEER, CIGARETTE_PACK };
			BulletsLink b = (BulletsLink)malloc(sizeof(BulletsLink));
			if (b == 0)
				Assert::Fail();
			b->next = 0;
			b->bullet = LIVE;

			bool dealer_cuffed = true;

			update_save(save, 0, 0, lives, items, 4, b, true, dealer_cuffed);
			output_save(save);
			destroy_save(save);
			save = create_save();

			input_save(save);

			Assert::AreEqual(dealer_cuffed, save->dealer_cuffed);

			destroy_save(save);
		}

		TEST_METHOD(SAV008) {
			int lives[2] = { 2, 2 };
			GAME_SAVE *save = create_save();
			ITEM_T items[4] = { BEER, MAGNIFYING_GLASS, BEER, CIGARETTE_PACK };
			BulletsLink b = (BulletsLink)malloc(sizeof(BulletsLink));
			if (b == 0)
				Assert::Fail();
			b->next = 0;
			b->bullet = LIVE;

			bool sawed = false;

			update_save(save, 0, 0, lives, items, 4, b, sawed, true);
			output_save(save);
			destroy_save(save);
			save = create_save();

			input_save(save);

			Assert::AreEqual(sawed, save->sawed);

			destroy_save(save);
		}

		TEST_METHOD(SAV009) {
			int lives[2] = { 2, 2 };
			INFINITE_SAVE *save = create_save_infinite();
			ITEM_T items[4] = { BEER, MAGNIFYING_GLASS, BEER, CIGARETTE_PACK };
			BulletsLink b = (BulletsLink)malloc(sizeof(BulletsLink));
			if (b == 0)
				Assert::Fail();
			b->next = 0;
			b->bullet = LIVE;

			bool sawed = false;
			unsigned long long wins = 8;

			update_save_inf(save, 0, 0, lives, items, 4, b, false, true, 8);
			output_save_inf(save);
			destroy_save_inf(save);
			save = create_save_infinite();

			input_save_inf(save);

			Assert::AreEqual(wins, save->total_wins);

			destroy_save_inf(save);
		}
	};
}
