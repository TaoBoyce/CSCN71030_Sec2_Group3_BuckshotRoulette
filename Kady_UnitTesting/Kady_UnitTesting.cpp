#include "CppUnitTest.h"
extern "C" {
#define INFSAVE_NAME "testinfsave"
#define SAVE_NAME "testsave"
#include "saveload.h"
#include "itemsHandler.h"
}

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace KadyUnitTesting
{
	TEST_CLASS(ItemHandlerTests)
	{
	public:
		
		TEST_METHOD(ItemAdd1)
		{
			for (int i = 0; i < 12; i++) {
				ITEM_T items[5] = { 0 };
				item_add(items, 5);
				Assert::IsTrue(items[0] > EMPTY && items[0] <= HAND_SAW);
			}
		}
		TEST_METHOD(ItemAdd2)
		{
			ITEM_T items[4] = { BEER, BEER, BEER, EMPTY };
			item_add(items, 4);
			Assert::AreNotEqual(items[3], (ITEM_T) EMPTY);
		}
		// Verifies that attempting adding to add item to full array will not crash
		TEST_METHOD(ItemAdd3)
		{
			ITEM_T items[4] = { BEER, BEER, BEER, BEER };
			item_add(items, 4);
		}

		TEST_METHOD(ItemText1) {
			Assert::AreEqual("Beer", item_text(BEER));
		}
		TEST_METHOD(ItemText2) {
			Assert::AreEqual("Empty", item_text(EMPTY));
		}
		TEST_METHOD(ItemText3) {
			Assert::AreEqual("Nill", item_text(-1));
		}

		TEST_METHOD(FindItem1) {
			ITEM_T items[4] = {BEER, HANDCUFFS, HAND_SAW, MAGNIFYING_GLASS};

			size_t index = findItem(HAND_SAW, items, 4);
			Assert::AreEqual(index, (size_t) 2);
		}
		TEST_METHOD(FindItem2) {
			ITEM_T items[4] = { EMPTY, EMPTY, HAND_SAW, MAGNIFYING_GLASS };

			size_t index = findItem(BEER, items, 4);
			Assert::AreEqual(index, (size_t) -1);
		}

		TEST_METHOD(ItemRemove1) {
			ITEM_T items[4] = { BEER, HANDCUFFS, HAND_SAW, MAGNIFYING_GLASS };

			item_remove(items, 3);

			Assert::AreEqual((ITEM_T) EMPTY, items[3]);
		}

		TEST_METHOD(ItemClear1) {
			ITEM_T items[4] = { BEER, HANDCUFFS, HAND_SAW, MAGNIFYING_GLASS };

			item_clear(items, 4);

			for (int i = 0; i < 4; i++) {
				Assert::AreEqual((ITEM_T) EMPTY, items[i]);
			}
		}
	};
	TEST_CLASS(SaveLoadTests) {
		TEST_METHOD(UpdateSave) {
			BulletsLink head = reinterpret_cast<BulletsLink>(malloc(sizeof(BulletsNode)));
			if (head == 0)
				Assert::Fail();
			head->bullet = BLANK;
			head->next = reinterpret_cast<BulletsLink>(malloc(sizeof(BulletsNode)));
			if (head->next == 0)
				Assert::Fail();
			head->next->bullet = LIVE;
			head->next->next = nullptr;

			GAME_SAVE *save = create_save();

			int arr[2] = { 2, 1 };
			ITEM_T arr2[2] = {BEER, MAGNIFYING_GLASS};
			update_save(save, 2, 2, (int *)arr, (ITEM_T*) arr2, 2, head, true, true);

			Assert::IsTrue(save->items[1] == (ITEM_T) MAGNIFYING_GLASS);
			Assert::IsTrue(save->bullets[1] == LIVE);
			Assert::IsTrue(save->lives[1] == 1);

			free(head->next);
			free(head);

			destroy_save(save);
		}
		TEST_METHOD(UpdateSaveInf) {
			BulletsLink head = reinterpret_cast<BulletsLink>(malloc(sizeof(BulletsNode)));
			if (head == 0)
				Assert::Fail();
			head->bullet = BLANK;
			head->next = reinterpret_cast<BulletsLink>(malloc(sizeof(BulletsNode)));
			if (head->next == 0)
				Assert::Fail();
			head->next->bullet = LIVE;
			head->next->next = nullptr;

			INFINITE_SAVE *save = create_save_infinite();

			int arr[2] = { 2, 1 };
			ITEM_T arr2[2] = { BEER, MAGNIFYING_GLASS };
			update_save_inf(save, 2, 2, (int *)arr, (ITEM_T*) arr2, 2, head, true, true, 5);

			Assert::IsTrue(save->items[1] == (ITEM_T)MAGNIFYING_GLASS);
			Assert::IsTrue(save->bullets[1] == LIVE);
			Assert::IsTrue(save->lives[1] == 1);
			Assert::IsTrue(save->total_wins == 5);

			free(head->next);
			free(head);

			destroy_save_inf(save);
		}
		TEST_METHOD(SaveLoad) {
			GAME_SAVE *save = create_save();
			int lvs[2] = { 1, 1 };
			ITEM_T items[2] = { BEER, HAND_SAW };
			BulletsLink b = (BulletsLink) malloc(sizeof(BulletsLink));
			if (b == 0)
				Assert::Fail();
			b->next = 0;
			b->bullet = LIVE;

			update_save(save, 1, 2, lvs, items, 2, b, true, false);

			output_save(save);

			destroy_save(save);
			save = create_save();

			input_save(save);

			Assert::IsTrue(save->sawed == true);
			Assert::IsTrue(save->items[0] == (ITEM_T) BEER);
			Assert::IsTrue(save->bullets[0] == LIVE);

			destroy_save(save);
		}
	};
}
