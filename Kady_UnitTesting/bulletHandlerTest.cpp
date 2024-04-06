#include "CppUnitTest.h"
extern "C" {
#include"bulletsHandler.h"
}

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace bulletHandlerTesting
{
	TEST_CLASS(bulletHandlerTest)
	{
	public:

		TEST_METHOD(addXbullets) {// should return x amount of bullets x=6
			//REQ-BLH-005

			int x = 6;

			BulletsLink bullets = NULL;

			loadRandomBullets(&bullets, x);

			Assert::AreEqual(x, bulletCount(bullets));

		}
		TEST_METHOD(popCorrectBullet) {
			//REQ-BLH-006

			BulletsLink head = NULL;

			addBullet(&head, LIVE);
			addBullet(&head, LIVE);
			addBullet(&head, BLANK);
			bullet poppedBullet = popBullet(&head);

			int num1 = BLANK;
			int num2 = poppedBullet;
			Assert::AreEqual(num1, num2);

		}

		TEST_METHOD(nextBulletCheck) {
			//REQ-BLH-007

			BulletsLink head = NULL;

			addBullet(&head, LIVE);
			addBullet(&head, BLANK);
			addBullet(&head, BLANK);

			bullet nextBullet = peekBullet(head);

			int num1 = nextBullet;
			int num2 = BLANK;

			Assert::AreEqual(num1, num2);

		}

		TEST_METHOD(clearGun) {

			BulletsLink head = NULL;

			loadRandomBullets(&head, 10);
			clearBullets(&head);



			Assert::IsNull(head);
		}
	};
}