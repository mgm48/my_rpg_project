#include "pch.h"
#include "CppUnitTest.h"
#include "playercharacter.h"
#include "item_manager.h"
#include "types.h"
#include "playableclasses.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace rpgsystemsunittest
{
	TEST_CLASS(rpgsystemsunittest){
	public:
		
		TEST_METHOD(LevelUpTest){
            //create test
			PlayerCharacter p1(new Warrior());
            Assert::AreEqual(Warrior::BASEHP, p1.GetMaxHP());

            //level up test
            p1.GiveExp(100u);
            Assert::AreEqual(p1.GetLevel(),(t_level)2);
            Assert::AreEqual((int)(Warrior::BASEHP + (Warrior::BASEHP / 2.f)), (int)p1.GetMaxHP());

            //abilities test
            Assert::AreEqual(std::string("PowerAttack"), p1.GetAbilityList().front().Name);
            
		}

        TEST_METHOD(ModifiersTest){
        
            PlayerCharacter p2(new Cleric());
            t_stat i_mod = 5;
            Buff int_buff("WeeklyPlanner", 10, 0, i_mod);

            //buff modifier and buff list test
            p2.ApplyBuff(int_buff);
            Assert::AreEqual(Cleric::BASEINT + i_mod, (int)p2.GetTotalIntellect());
            Assert::AreEqual(p2.GetBuffList().front().Name, int_buff.Name);

            //debuff test, stat limit test
            t_stat st_mod = -4;
            Buff str_debuff("MondayBlues", 10, st_mod);
            p2.ApplyBuff(str_debuff);
            Assert::AreEqual(1, (int)p2.GetTotalStrength());
        }

        TEST_METHOD(InventoryTest){
            //equip test
            PlayerCharacter p3(new Wizard());

            //no rest on level up test
            p3.GiveExp(100u);
            Assert::AreEqual(Wizard::BASEHP, p3.GetCurrentHP());

            Assert::IsFalse(ItemManager::Equip(
                ItemManager::CreatePotion("ArmorPot", 0, 1, new Buff("ArmorBuff", CoreStats(0, 0, 0, 3, 0), 5)),
                &p3));

            Item* HealPotion = ItemManager::CreatePotion("Heal Potion", 3u, 1u);
            Assert::IsTrue(ItemManager::MoveToBackpack(HealPotion, &p3));
            Assert::AreEqual((std::string)"Heal Potion", p3.GetBackpackList().front()->GetData()->Name);

            Assert::IsTrue(ItemManager::Use(HealPotion, &p3));

            Assert::IsTrue(p3.GetBackpackList().empty());
        }
        TEST_METHOD(EquipTest)
        {
            PlayerCharacter p4(new Rogue());
            Assert::IsTrue(ItemManager::Equip(
                ItemManager::CreateWeapon("Dagger", CoreStats(), WEAPONSLOT::MELEE, 1, 3, false), &p4));
            Assert::IsTrue(ItemManager::Equip(
                ItemManager::CreateArmor("Shiny Plate Armor", CoreStats(0, 0, 0, 5, 3), ARMORSLOT::CHEST), &p4));

            Assert::IsNotNull(p4.GetEquippedWeaponAt((unsigned long long)WEAPONSLOT::MELEE));
            Assert::IsNotNull(p4.GetEquippedArmorAt((unsigned long long)ARMORSLOT::CHEST));

            //Item* FullPlateMail = ItemManager::CreateArmor("Shiny Plate Armor", CoreStats(0, 0, 0, 5, 3), ARMORSLOT::CHEST);
            //Item* LeatherArmor = ItemManager::CreateArmor("Leather Armor", CoreStats(0, 0, 0, 2, 1), ARMORSLOT::CHEST);

        }
        TEST_METHOD(WeaponItem) {
            Item* a_magic_weapon
                = ItemManager::CreateWeapon("Magic Weapon", CoreStats(5,5,5,5,5), WEAPONSLOT::MELEE, 1, 3, false);
            Assert::IsNotNull(a_magic_weapon);
            Assert::IsTrue(ItemManager::IsItemWeapon(a_magic_weapon));
            Assert::IsFalse(ItemManager::IsItemArmor(a_magic_weapon));
            Assert::IsFalse(ItemManager::IsItemPotion(a_magic_weapon));
            // cast item data to weapon to check if it is a weapon
            Weapon* weapon = nullptr;
            ItemManager::CastItemToWeapon(a_magic_weapon, weapon);
            Assert::IsNotNull(weapon);  // make sure cast doesn't fail
            Assert::AreEqual(std::string("Magic Weapon"), weapon->Name);
            Assert::AreEqual(5, (int)weapon->Stats.Strength);
            Assert::AreEqual(5, (int)weapon->Stats.Intellect);
            Assert::AreEqual(5, (int)weapon->Stats.Agility);
            Assert::AreEqual(5, (int)weapon->Stats.Armor);
            Assert::AreEqual(5, (int)weapon->Stats.ElementRes);
            Assert::AreEqual((int)WEAPONSLOT::MELEE, (int)weapon->Slot);
            Assert::AreEqual(1, (int)weapon->MinDamage);
            Assert::AreEqual(3, (int)weapon->MaxDamage);
            Assert::IsFalse(weapon->is2H);
            ItemManager::DeleteItem(a_magic_weapon); 
            Assert::IsNull(a_magic_weapon);
            //doesnt matter in this case, but in other cases weapon should be = to nullptr so it doesnt become a dangling cast/pointer
            //to delete an item that can be casted into another class, we need to get rid of both
        }
	};
}
