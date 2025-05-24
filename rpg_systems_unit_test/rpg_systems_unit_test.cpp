#include "pch.h"
#include "CppUnitTest.h"
#include "playercharacter.h"
#include "item_manager.h"
#include "types.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace rpgsystemsunittest
{
	TEST_CLASS(rpgsystemsunittest)
	{
	public:
		
		TEST_METHOD(LevelUpTest)
		{
            //create test
			PlayerCharacter p1(new Warrior());
            Assert::AreEqual(Warrior::BASEHP, p1.getMaxHP());

            //level up test
            p1.gainExp(100u);
            Assert::AreEqual(p1.getLevel(),(t_level)2);
            Assert::AreEqual((int)(Warrior::BASEHP + (Warrior::BASEHP / 2.f)), (int)p1.getMaxHP());

            //abilities test
            Assert::AreEqual(std::string("PowerAttack"), p1.getAbilityList().front().Name);
            
		}

        TEST_METHOD(ModifiersTest)
        {

            PlayerCharacter p2(new Cleric());
            t_stat i_mod = 5;
            IntellectBuff int_buff("WeeklyPlanner", 10, i_mod);

            //buff modifier and buff list test
            p2.applyBuff(int_buff);
            Assert::AreEqual(Cleric::BASEINT + i_mod, (int)p2.getTotalIntellect());
            Assert::AreEqual(p2.getBuffList().front().Name, int_buff.Name);

            //debuff test, stat limit test
            t_stat st_mod = -4;
            StrengthBuff str_debuff("MondayBlues", 10, st_mod);
            p2.applyBuff(str_debuff);
            Assert::AreEqual(1, (int)p2.getTotalStrength());
            Assert::AreEqual(st_mod, p2.getStrengthModifier());
        }

        TEST_METHOD(InventoryTest)
        {
            //equip test
            PlayerCharacter p3(new Wizard());

            //no rest on level up test
            p3.gainExp(100u);
            Assert::AreEqual(Wizard::BASEHP, p3.getCurrentHP());

            Assert::IsFalse(ItemManager::Equip(
                ItemManager::CreatePotion("ArmorPot", 0, 1, new Buff("ArmorBuff", CoreStats(0, 0, 0, 3, 0), 5)),
                &p3));

            Item* HealPotion = ItemManager::CreatePotion("Heal Potion", 3u, 1u);
            Assert::IsTrue(ItemManager::MoveToBackpack(HealPotion, &p3));
            Assert::AreEqual((std::string)"Heal Potion", p3.getBackpackList().front()->GetData()->Name);

            Assert::IsTrue(ItemManager::Use(HealPotion, &p3));

            Assert::IsTrue(p3.getBackpackList().empty());
        }
        TEST_METHOD(EquipTest)
        {
            PlayerCharacter p4(new Rogue());
            Assert::IsTrue(ItemManager::Equip(
                ItemManager::CreateWeapon("Dagger", CoreStats(), WEAPONSLOT::MELEE, 1, 3, false), &p4));
            Assert::IsTrue(ItemManager::Equip(
                ItemManager::CreateArmor("Shiny Plate Armor", CoreStats(0, 0, 0, 5, 3), ARMORSLOT::CHEST), &p4));

            Assert::IsNotNull(p4.getEquippedWeaponAt((unsigned long long)WEAPONSLOT::MELEE));
            Assert::IsNotNull(p4.getEquippedArmorAt((unsigned long long)ARMORSLOT::CHEST));

            //Item* FullPlateMail = ItemManager::CreateArmor("Shiny Plate Armor", CoreStats(0, 0, 0, 5, 3), ARMORSLOT::CHEST);
            //Item* LeatherArmor = ItemManager::CreateArmor("Leather Armor", CoreStats(0, 0, 0, 2, 1), ARMORSLOT::CHEST);

        }
	};
}
