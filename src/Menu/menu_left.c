#include "Game/game.h"
#include "Game/linkvarbuf.h"
#include "libdg/libdg.h"
#include "menuman.h"
#include "radio.h"
#include "linker.h"
#include "psyq.h"
#include "Game/game.h"

extern PANEL_TEXTURE gMenuLeftItems_800BD5A0[];
extern menu_weapon_rpk_info      gMenuItemRpkInfo_8009E484[];

extern short                     GM_WeaponTypes_8009D580[];
extern short                     GM_ItemTypes_8009D598[];
extern int                       GM_GameStatus_800AB3CC;
extern int                       GM_PlayerStatus_800ABA50;
extern int                       GV_PauseLevel_800AB928;
extern int                       GM_DisableItem_800ABA28;
extern int                       DG_UnDrawFrameCount_800AB380;
extern int                       dword_8009F46C;

extern int                       dword_800ABAD0;
int SECTION(".sbss")             dword_800ABAD0;

extern int                       dword_800AB574;
int SECTION(".sbss")             dword_800AB574;

extern int                       dword_800AB578;
int SECTION(".sbss")             dword_800AB578;

extern const char aNoItem[];
extern const char aLv[];
extern const char aEquip[];  // = "EQUIP"

void sub_8003CEF8(PANEL_TEXTURE *a1);
int  menu_number_draw_number2_80042FC0(Actor_MenuMan *pActor, int xpos, int ypos, int current, int total);
void menu_init_sprt_8003D0D0(SPRT *pPrim, PANEL_TEXTURE *pUnk, int offset_x, int offset_y);
int  menu_number_draw_string_800430F0(Actor_MenuMan *pActor, unsigned int *pOt, int xpos, int ypos, const char *str, int flags);
void menu_sub_menu_update_8003DA0C(struct Actor_MenuMan *pActor, unsigned int *pOt, Menu_Inventory *pSubMenu);
void Menu_item_render_frame_rects_8003DBAC(MenuPrim *pGlue, int x, int y, int param_4);
int  menu_8003D538(void);
void menu_8003D7DC(Actor_MenuMan *pActor, unsigned int *pOt, Menu_Inventory *pSubMenu);
int  sub_8003D568(void);

void menu_sub_8003B568(void)
{
    int   imgIdx;
    u_long palIdx;
    int   i;

    for (i = 0; i < MENU_ITEM_COUNT; i++)
    {
        imgIdx = 0xc + i;
        palIdx = 0x2e;
        if (imgIdx != 0x16)
        {
            palIdx = 0;
            if (imgIdx == 0x1b)
            {
                palIdx = 0x2f;
            }
        }
        menu_init_rpk_item_8003DDCC(&gMenuLeftItems_800BD5A0[i], imgIdx, palIdx);
    }
}

PANEL_TEXTURE * menu_rpk_8003B5E0(int index)
{
    return &gMenuLeftItems_800BD5A0[gMenuItemRpkInfo_8009E484[index].field_4_rpk_idx - 12];
}

extern char *itm_descriptions_8009E3E4[];
extern void *dword_8009E444[];
extern void *dword_8009E44C[];

void menu_8003B614(int index)
{
    char *ptr = itm_descriptions_8009E3E4[index];

    if (GM_FrozenItemsState == 1)
    {
        if (index != ITEM_KETCHUP)
        {
            if (index == ITEM_RATION)
            {
                ptr = dword_8009E444[0];
            }
        }
        else
        {
            ptr = dword_8009E444[1];
        }
    }

    if (index == ITEM_CARD)
    {
        ptr[46] = GM_CardFlag + 48;
    }

    if (index == ITEM_MINE_D && GM_DifficultyFlag >= DIFFICULTY_HARD)
    {
        ptr = (char *)dword_8009E44C;
    }

    sub_8003F97C(ptr);
}

int menu_item_IsItemDisabled_8003B6D0(int item)
{
    int bit;

    if ((GM_WeaponTypes_8009D580[GM_CurrentWeaponId + 1] & 0x200) &&
        (GM_ItemTypes_8009D598[item + 1] & 1))
    {
        return 1;
    }

    if (GM_PlayerStatus_800ABA50 & (PLAYER_PRONE | PLAYER_FIRST_PERSON_DUCT))
    {
        if ((item == ITEM_C_BOX_A) ||
            (item == ITEM_C_BOX_B) ||
            (item == ITEM_C_BOX_C))
        {
            return 1;
        }
    }

    if (dword_8009F46C != 0)
    {
        if ((item == ITEM_SCOPE)   ||
            (item == ITEM_C_BOX_A) ||
            (item == ITEM_C_BOX_B) ||
            (item == ITEM_C_BOX_C) ||
            (item == ITEM_CAMERA))
        {
            return 1;
        }
    }

    bit = 1 << item;
    return (GM_DisableItem_800ABA28 & bit) != 0;
}

void menu_8003B794(Actor_MenuMan *pActor, unsigned int *pOt, int id)
{
    RECT pal_rect;
    RECT img_rect;
    Menu_rpk_item *pPalItem;
    Menu_rpk_item *pImgItem;
    SPRT *pSprt;

    pPalItem = menu_rpk_get_pal_8003DD9C(id * 2 + 33);
    pImgItem = menu_rpk_get_img_8003DDB4(id * 2 + 34);

    pal_rect.x = 960;
    pal_rect.y = 336;
    pal_rect.w = 16;
    pal_rect.h = 1;
    LoadImage_8008FB10(&pal_rect, pPalItem->field_4_pixel_ptr);

    img_rect.x = 960;
    img_rect.y = 337;
    img_rect.w = pImgItem->field_2_w;
    img_rect.h = pImgItem->field_3_h;
    LoadImage_8008FB10(&img_rect, pImgItem->field_4_pixel_ptr);

    NEW_PRIM(pSprt, pActor);

    pSprt->v0 = 81;
    pSprt->x0 = 230;
    pSprt->u0 = 0;
    pSprt->y0 = 116;
    pSprt->w = pImgItem->field_2_w * 4;
    pSprt->h = pImgItem->field_3_h;
    LSTORE(0x80808080, &pSprt->r0);
    pSprt->clut = getClut(pal_rect.x, pal_rect.y);
    setSprt(pSprt);
    addPrim(pOt, pSprt);
}



void menu_item_helper_8003B8F0(struct Actor_MenuMan *pActor, unsigned int *pOt, int xpos, int ypos, Menu_Inventory *pMenuSub)
{
    PANEL_TEXTURE *pMenuSprt; // $s6
    SPRT          *pIconSprt; // $s0
    int           rgb; // $s1
    int           bBlueBackground; // $a3
    TextConfig    textConfig; // [sp+18h] [-10h] BYREF

    if ( pMenuSub->field_0_current.field_0_id >= 0 )
    {
        pMenuSprt = menu_rpk_8003B5E0(pMenuSub->field_0_current.field_0_id);
        sub_8003CEF8(pMenuSprt);
        if ( menu_item_IsItemDisabled_8003B6D0(pMenuSub->field_0_current.field_0_id) )
        {
            menu_draw_nouse_800435A4(pActor->field_20_otBuf, xpos, ypos);
        }
        if ( GM_FrozenItemsState == 1 )
        {
            if ( pMenuSub->field_0_current.field_0_id == ITEM_RATION ||
                 pMenuSub->field_0_current.field_0_id == ITEM_KETCHUP )
            {
                menu_draw_frozen_800435C8(pActor->field_20_otBuf, xpos, ypos);
            }
        }

        if ( GM_ItemTypes_8009D598[pMenuSub->field_0_current.field_0_id + 1] & ITEMTYPE_CONSUMABLE )
        {
            menu_number_draw_number2_80042FC0(
                pActor,
                xpos,
                ypos + 11,
                pMenuSub->field_0_current.field_2_num,
                GM_ItemsMax[pMenuSub->field_0_current.field_0_id]);
        }
        else if ( pMenuSub->field_0_current.field_0_id == ITEM_CARD )
        {
            textConfig.xpos = xpos;
            textConfig.ypos = ypos + 14;
            textConfig.flags = 0;
            textConfig.colour = 0x64808080;
            menu_number_draw_string_80042BF4(pActor->field_20_otBuf, &textConfig, aLv);
            textConfig.ypos -= 2;
            menu_number_draw_80042988(pActor->field_20_otBuf, &textConfig, GM_Items[ITEM_CARD]);
        }
        else if ( pMenuSub->field_0_current.field_0_id == ITEM_TIMER_B )
        {
            menu_number_draw_80042F78(
                pActor,
                pOt,
                xpos + 10,
                ypos + 10,
                GM_Items[ITEM_TIMER_B],
                0);
        }

        if ( pMenuSprt->field_C_uvclut )
        {
            NEW_PRIM(pIconSprt, pActor);

            if ( !pMenuSub->field_0_current.field_4_pos )
            {
                rgb = 0x808080;
            }
            else
            {
                rgb = 0x404040;
            }
            menu_init_sprt_8003D0D0(pIconSprt, pMenuSprt, xpos, ypos);
            LSTORE(rgb, &pIconSprt->r0);
            setSprt(pIconSprt);
            addPrim(pOt, pIconSprt);
        }
        menu_number_draw_string_800430F0(
            pActor,
            pOt,
            xpos + 46,
            ypos + 22,
            gMenuItemRpkInfo_8009E484[pMenuSub->field_0_current.field_0_id].field_0_weapon_name,
            1);
    }
    else
    {
        menu_number_draw_string_800430F0(pActor, pOt, xpos + 46, ypos + 22, aNoItem, 1);
    }

    if ( !pMenuSub->field_0_current.field_4_pos )
    {
        bBlueBackground = pMenuSub->field_0_current.field_6_current == 0;
    }
    else
    {
        bBlueBackground = 0;
    }

    Menu_item_render_frame_rects_8003DBAC(pActor->field_20_otBuf, xpos, ypos, bBlueBackground);
}

void menu_8003BBEC(Actor_MenuMan *pActor)
{
    Menu_Item_Unknown *temp_v0 = pActor->field_1DC_menu_item.field_C_alloc;
    int index;
    short *pLinkVar;

    pActor->field_1DC_menu_item.field_10_state = 0;

    AssignXYFromVec_8003D1B8(&pActor->field_1DC_menu_item.field_0_current, &temp_v0->field_20_array[temp_v0->field_0_main.field_4_selected_idx]);

    if (pActor->field_1DC_menu_item.field_0_current.field_2_num <= 0)
    {
        pActor->field_1DC_menu_item.field_0_current.field_0_id = ITEM_NONE;
    }

    index = pActor->field_1DC_menu_item.field_0_current.field_0_id;
    pLinkVar = linkvarbuf;

    if ((index >= 0) && !menu_item_IsItemDisabled_8003B6D0(index))
    {
        pLinkVar[15] = index;
        sub_8003CFE0(menu_rpk_8003B5E0(index), 0);
        pActor->field_1DC_menu_item.field_11 = pLinkVar[15];
    }
    else
    {
        if (index != ITEM_NONE)
        {
            dword_800ABAD0 = index;
        }

        GM_CurrentItemId = ITEM_NONE;
        pActor->field_1DC_menu_item.field_0_current.field_0_id = ITEM_NONE;
    }

    pActor->field_1DC_menu_item.field_12_flashingAnimationFrame = 10;

    menu_panel_free_8003D184(pActor->field_1DC_menu_item.field_C_alloc);
    menu_font_kill_8003FC0C();

    GM_SeSet2_80032968(0, 63, 20);
}

int menu_item_update_helper_8003BCD4(Actor_MenuMan *pActor)
{
    int activeItems;
    int i;
    Menu_Item_Unknown *pPanels;
    int cardVal;
    int panelIndex;

    if (!(GM_GameStatus_800AB3CC & 0x40000))
    {
        activeItems = 0;

        for (i = 0; i < GM_TotalItems; i++)
        {
            if (GM_Items[i] > 0)
            {
                activeItems++;
            }
        }

        pPanels = menu_alloc_panel_8003D124(activeItems + 1);
        pActor->field_1DC_menu_item.field_C_alloc = pPanels;

        if (!pPanels)
        {
            return 0;
        }

        if ((GM_CurrentItemId != ITEM_NONE) && (GM_CurrentItemId != ITEM_CARD))
        {
            dword_800ABAD0 = GM_CurrentItemId;
        }
        else if (dword_800ABAD0 < 0)
        {
            dword_800ABAD0 = 0;
        }

        cardVal = -1;

        if (GM_CardFlag > 0)
        {
            cardVal = 0;
        }

        panelIndex = 0;

        for (i = 0; i < GM_TotalItems; i++)
        {
            if (i == dword_800ABAD0)
            {
                AssignXY_8003D1A8(&pPanels->field_20_array[panelIndex], ITEM_NONE, 1);

                panelIndex++;

                if (cardVal == 0)
                {
                    if (GM_CurrentItemId == ITEM_NONE)
                    {
                        AssignXY_8003D1A8(&pPanels->field_20_array[panelIndex], ITEM_CARD, GM_Items[ITEM_CARD]);
                        panelIndex++;
                    }
                    else
                    {
                        cardVal = 1;
                    }
                }
            }

            if ((GM_Items[i] > 0) && (i != ITEM_CARD))
            {
                AssignXY_8003D1A8(&pPanels->field_20_array[panelIndex], i, GM_Items[i]);
                panelIndex++;
            }

            if (cardVal > 0)
            {
                AssignXY_8003D1A8(&pPanels->field_20_array[panelIndex], ITEM_CARD, GM_Items[ITEM_CARD]);
                panelIndex++;
                cardVal = 0;
            }
        }
    }
    else
    {
        pPanels = menu_alloc_panel_8003D124(1);
        pActor->field_1DC_menu_item.field_C_alloc = pPanels;

        if (!pPanels)
        {
            return 0;
        }

        AssignXY_8003D1A8(&pPanels->field_20_array[0], ITEM_NONE, 1);
    }

    if (!sub_8003F84C(0))
    {
        menu_panel_free_8003D184(pPanels);
        return 0;
    }

    dword_800AB578 = 0;
    dword_800AB574 = 0;
    pActor->field_1DC_menu_item.field_10_state = 2;

    sub_8003D520();
    sub_8003CE40(gMenuLeftItems_800BD5A0, MENU_ITEM_COUNT);
    menu_panel_8003D2BC(pActor->field_1DC_menu_item.field_C_alloc, pActor->field_1DC_menu_item.field_0_current.field_0_id);
    GM_SeSet2_80032968(0, 63, 21);
    return 1;
}

void menu_item_update_helper2_8003BF1C(Actor_MenuMan *pActor, unsigned int *pOt)
{
    unsigned short anim_frame;
    int anim_frame2;
    int switched_weapon;
    int last_id;
    Menu_Item_Unknown *pAlloc;
    PANEL *pPanel;

    switch (pActor->field_1DC_menu_item.field_10_state)
    {
    case 0:
        anim_frame = pActor->field_1DC_menu_item.field_12_flashingAnimationFrame & 0xffff;
        anim_frame2 = anim_frame & 0xffff;

        if (anim_frame2 != 0)
        {
            pActor->field_1DC_menu_item.field_12_flashingAnimationFrame--;

            if ((anim_frame2 & 3) > 1)
            {
                menu_sub_menu_update_8003DA0C(pActor, pOt, &pActor->field_1DC_menu_item);

                if (((anim_frame2 & 3) == 3) &&
                    (pActor->field_1DC_menu_item.field_0_current.field_0_id != GM_CurrentItemId) &&
                    menu_item_IsItemDisabled_8003B6D0(pActor->field_1DC_menu_item.field_0_current.field_0_id) &&
                    (DG_UnDrawFrameCount_800AB380 == 0))
                {
                    GM_SeSet2_80032968(0, 63, 54);
                    break;
                }
            }
        }
        else
        {
            switched_weapon = 0;
            if (menu_item_IsItemDisabled_8003B6D0(GM_CurrentItemId))
            {
                last_id = GM_CurrentItemId;
                GM_CurrentItemId = ITEM_NONE;
                pActor->field_1DC_menu_item.field_12_flashingAnimationFrame = 19;
                dword_800ABAD0 = last_id;
                break;
            }

            if (pActor->field_1DC_menu_item.field_0_current.field_0_id != GM_CurrentItemId)
            {
                switched_weapon = 1;

                if (pActor->field_1DC_menu_item.field_0_current.field_0_id != ITEM_NONE &&
                    pActor->field_1DC_menu_item.field_0_current.field_0_id != ITEM_CARD)
                {
                    dword_800ABAD0 = pActor->field_1DC_menu_item.field_0_current.field_0_id;
                }

                pActor->field_1DC_menu_item.field_0_current.field_0_id = GM_CurrentItemId;
            }

            if (GM_CurrentItemId >= 0)
            {
                if (switched_weapon != 0)
                {
                    sub_8003CFE0(menu_rpk_8003B5E0(GM_CurrentItemId), 0);
                    pActor->field_1DC_menu_item.field_11 = GM_CurrentItemId;
                }

                pActor->field_1DC_menu_item.field_0_current.field_2_num = GM_Items[GM_CurrentItemId];
                menu_sub_menu_update_8003DA0C(pActor, pOt, &pActor->field_1DC_menu_item);
            }
        }
        break;

    case 2:
        if (menu_8003D538())
        {
            pActor->field_1DC_menu_item.field_10_state = 1;
        }

        dword_800AB574 = 0;

    case 1:
        pAlloc = pActor->field_1DC_menu_item.field_C_alloc;
        pPanel = &pAlloc->field_20_array[pAlloc->field_0_main.field_4_selected_idx];

        if (GM_GameStatus_800AB3CC & 0x1000)
        {
            dword_800AB578 = 0;
            dword_800AB574 = 0;
        }

        if ((pPanel->field_4_pos == 0) && (pPanel->field_0_id >= 0))
        {
            if (dword_800AB578 == 0)
            {
                if (++dword_800AB574 == 4)
                {
                    menu_8003B614(pPanel->field_0_id);
                    dword_800AB578 = 1;
                }
            }
        }
        else
        {
            dword_800AB578 = 0;
            dword_800AB574 = 0;
        }

        if (dword_800AB578 != 0)
        {
            if (pPanel->field_0_id == ITEM_PAL_KEY)
            {
                menu_8003B794(pActor, pOt, GM_ShapeKeyState);
            }

            menu_8003F9B4(pActor, pOt, aEquip);
        }

        menu_8003D7DC(pActor, pOt, &pActor->field_1DC_menu_item);
        break;

    case 3:
        if (sub_8003D568() != 0)
        {
            pActor->field_2A_state = 0;
            GV_PauseLevel_800AB928 &= ~0x4;
            menu_8003BBEC(pActor);
        }
        else
        {
            menu_8003D7DC(pActor, pOt, &pActor->field_1DC_menu_item);
        }
        break;
    }
}

void menu_item_update_helper3_8003C24C(Menu_Item_Unknown *pPanels, unsigned short press)
{
    PANEL *pPanel;
    short  heal_amount;
    short  item_amount;

    if (!(press & PAD_CIRCLE))
    {
        return;
    }

    pPanel = &pPanels->field_20_array[pPanels->field_0_main.field_4_selected_idx];

    if (pPanel->field_2_num <= 0)
    {
        return;
    }

    switch(pPanel->field_0_id)
    {
    case ITEM_KETCHUP:
    case ITEM_RATION:
        if (GM_FrozenItemsState != 0)
        {
            GM_SeSet2_80032968(0, 63, 115); // Frozen item ding
            return;
        }

        if (GM_SnakeCurrentHealth == GM_SnakeMaxHealth)
        {
            GM_SeSet2_80032968(0, 63, 35); // "BA BA" denied sound
            return;
        }

        if (pPanel->field_0_id == ITEM_RATION)
        {
            if (GM_DifficultyFlag == DIFFICULTY_VERY_EASY)
            {
                heal_amount = 1024;
            }
            else if (GM_DifficultyFlag == DIFFICULTY_EASY)
            {
                heal_amount = 384;
            }
            else
            {
                heal_amount = 256;
            }
        }
        else
        {
            heal_amount = 64;
            pPanel->field_0_id = ITEM_NONE;
            GM_KetchupFlag = 0;
        }

        GM_SnakeCurrentHealth += heal_amount;
        GM_TotalRationsUsed++;

        if (GM_SnakeCurrentHealth > GM_SnakeMaxHealth)
        {
            GM_SnakeCurrentHealth = GM_SnakeMaxHealth;
        }

        GM_SeSet2_80032968(0, 63, 12); // Ration used sound
        break;

    case ITEM_MEDICINE:
        if (GM_StatusEvent & EV_CommonCold) // Snake has a cold :(
        {
            GM_StatusEvent &= ~EV_CommonCold;
            GM_SnakeColdTimer = 0;
            GM_SnakeColdUnk9A = 0;
        }

        GM_SeSet2_80032968(0, 63, 34); // Medicine used sound
        break;

    case ITEM_DIAZEPAM:
        GM_StatusEvent |= EV_Tranquilizer;

        if (GM_TranquilizerTimer < 0)
        {
            GM_TranquilizerTimer = 0;
        }

        GM_TranquilizerTimer += 1200;

        GM_SeSet2_80032968(0, 63, 34); // Medicine used sound
        break;

    case ITEM_TIMER_B:
        if ( (GM_PlayerStatus_800ABA50 & 0x362) ||
             dword_8009F46C ||
             menu_item_IsItemDisabled_8003B6D0(ITEM_TIMER_B) )
        {
            GM_SeSet2_80032968(0, 63, 35); // "BA BA" denied sound
        }
        else
        {
            pPanel->field_0_id = ITEM_NONE;
            GM_TimerBombFlag = ITEM_NONE;
            GM_PlayerStatus_800ABA50 |= PLAYER_THROWING;
            GM_SeSet2_80032968(0, 63, 33); // Title screen exit/bomb discard sound
        }
        return;

    default:
        return;
    }

    if (pPanel->field_0_id >= 0)
    {
        item_amount = GM_Items[pPanel->field_0_id];
        pPanel->field_2_num = item_amount - 1;
        GM_Items[pPanel->field_0_id] = item_amount - 1;
    }
}

#pragma INCLUDE_ASM("asm/Menu/menu_item_update_helper4_8003C4EC.s") // 1136 bytes

void menu_item_update_8003C95C(Actor_MenuMan *pActor, unsigned int *pOt)
{
    GV_PAD          *pPad = pActor->field_24_pInput;
    Menu_Inventory  *pLeftRight;

    if (pActor->field_2A_state == 0)
    {
        if (!(GM_GameStatus_800AB3CC & 0x80400))
        {
            if (!(GM_PlayerStatus_800ABA50 & (PLAYER_PAD_OFF | PLAYER_PREVENT_ITEM_SWITCH |
                                              PLAYER_PREVENT_WEAPON_ITEM_SWITCH)))
            {
                if (menu_8003DA9C(&pActor->field_1DC_menu_item, pPad))
                {
                    if (menu_item_update_helper_8003BCD4(pActor))
                    {
                        pActor->field_2A_state = 2;
                        GV_PauseLevel_800AB928 |= 4;
                    }
                }
                else if (!(GM_GameStatus_800AB3CC & 0x40000) && (pPad->press & PAD_L1))
                {
                    int itemid = GM_CurrentItemId;

                    if (itemid >= 0)
                    {
                        GM_CurrentItemId = -1;
                    }
                    else if (!menu_item_IsItemDisabled_8003B6D0(pActor->field_1DC_menu_item.field_11))
                    {
                        if (GM_Items[pActor->field_1DC_menu_item.field_11] > 0)
                        {
                            GM_CurrentItemId = pActor->field_1DC_menu_item.field_11;
                        }
                    }

                    if (itemid != GM_CurrentItemId)
                    {
                        GM_SeSet2_80032968(0, 63, 20);
                    }
                }
            }
        }
        else
        {
            return;
        }
    }
    else if (pActor->field_2A_state == 2)
    {
        pLeftRight = &pActor->field_1DC_menu_item;

        if (sub_8003DAFC(pLeftRight, pPad))
        {
            pActor->field_1DC_menu_item.field_10_state = 3;
        }
        else if (sub_8003D52C() > 255)
        {
            sub_8003D6CC(pLeftRight, pPad);
            menu_item_update_helper3_8003C24C(pActor->field_1DC_menu_item.field_C_alloc, pPad->press);
        }
    }
    else if (pActor->field_2A_state != 4)
    {
        if (GM_CurrentItemId >= 0)
        {
            int ret = sub_8003D52C();
            if (ret < 255)
            {
                sub_8003DA60(pActor, pOt, &pActor->field_1DC_menu_item, -ret / 4, 0);
                pActor->field_1DC_menu_item.field_12_flashingAnimationFrame = 0;
            }
        }
        else
        {
            pActor->field_1DC_menu_item.field_12_flashingAnimationFrame = 0;
        }
        return;
    }
    else
    {
        return;
    }

    menu_item_update_helper2_8003BF1C(pActor, pOt);
    menu_item_update_helper4_8003C4EC();
}

void sub_8003CB98(struct Actor_MenuMan *pActor)
{
    int            field_0_item_id_idx; // $a0
    PANEL_TEXTURE *pItem; // $v0

    menu_restore_nouse_80043470();
    field_0_item_id_idx = pActor->field_1DC_menu_item.field_0_current.field_0_id;
    if ( field_0_item_id_idx != ITEM_NONE
      || (field_0_item_id_idx = pActor->field_1DC_menu_item.field_11, field_0_item_id_idx != ITEM_NONE) )
    {
        pItem = menu_rpk_8003B5E0(field_0_item_id_idx);
        sub_8003CFE0(pItem, 0);
    }
}

void menu_item_8003CBF0(struct Actor_MenuMan *menuMan)
{
    short val = -1;

    menuMan->field_2C_modules[MENU_ITEM] = (TMenuUpdateFn)menu_item_update_8003C95C;
    menuMan->field_1DC_menu_item.field_0_current.field_0_id = val;
    menuMan->field_1DC_menu_item.field_10_state = 0;
    menuMan->field_1DC_menu_item.field_0_current.field_4_pos = 0;
    menuMan->field_1DC_menu_item.field_0_current.field_6_current = 1;
    menuMan->field_1DC_menu_item.field_11 = val;
    menuMan->field_28_flags |= 4;
    dword_800ABAD0 = 0;
    sub_8003D6A8(&menuMan->field_1DC_menu_item, 0, (int *)menu_item_helper_8003B8F0);
    menu_sub_8003B568();
    sub_8003CB98(menuMan);
    menu_init_nouse_800434A8();
}

void menu_item_kill_8003CC74(Actor_MenuMan *pMenu)
{
    pMenu->field_28_flags &= ~4u;
}
