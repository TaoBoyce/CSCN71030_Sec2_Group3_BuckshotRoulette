#include "CppUnitTest.h"
extern "C" {
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
}
