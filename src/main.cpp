#include <Geode/Geode.hpp>
#include <Geode/binding/FLAlertLayer.hpp>
#include <Geode/binding/CCMenuItemSpriteExtra.hpp>
#include <string>

using namespace geode::prelude;

class VersusVisualTradeLayer : public FLAlertLayer {
public:
    static VersusVisualTradeLayer* create() {
        auto ret = new VersusVisualTradeLayer();
        if (ret && ret->init()) {
            ret->autorelease();
            return ret;
        }
        CC_SAFE_DELETE(ret);
        return nullptr;
    }

    bool init() {
        if (!FLAlertLayer::init(180)) return false;

        auto winSize = CCDirector::sharedDirector()->getWinSize();
        
        // 1. Core Window Frame Backdrop Panel Box
        auto bg = CCScale9Sprite::create("GJ_square02.png");
        bg->setContentSize({ 360, 250 });
        bg->setPosition(winSize / 2);
        this->m_mainLayer->addChild(bg);

        // 2. Decorative Dark Content Background Dividers
        // Top Box (Your Side)
        auto topSection = CCScale9Sprite::create("square02b_001.png");
        topSection->setContentSize({ 330, 80 });
        topSection->setPosition({ winSize.width / 2, winSize.height / 2 + 45 });
        topSection->setOpacity(100);
        this->m_mainLayer->addChild(topSection);

        // Bottom Box (Their Side)
        auto bottomSection = CCScale9Sprite::create("square02b_001.png");
        bottomSection->setContentSize({ 330, 80 });
        bottomSection->setPosition({ winSize.width / 2, winSize.height / 2 - 45 });
        bottomSection->setOpacity(100);
        this->m_mainLayer->addChild(bottomSection);

        // 3. UI Section Heading Labels
        auto topHeader = CCLabelBMFont::create("YOUR TRANSACTION OFFER", "goldFont.fnt");
        topHeader->setPosition({ winSize.width / 2 - 60, winSize.height / 2 + 75 });
        topHeader->setScale(0.45f);
        this->m_mainLayer->addChild(topHeader);

        auto bottomHeader = CCLabelBMFont::create("THEIR TRANSACTION OFFER", "goldFont.fnt");
        bottomHeader->setPosition({ winSize.width / 2 - 60, winSize.height / 2 - 15 });
        bottomHeader->setScale(0.45f);
        this->m_mainLayer->addChild(bottomHeader);

        // 4. Item Detail Placeholders (Dynamically tracked in production)
        auto yourItemsLabel = CCLabelBMFont::create("Giving: 10 Stars | 2,500 Mana Orbs", "bigFont.fnt");
        yourItemsLabel->setPosition({ winSize.width / 2, winSize.height / 2 + 45 });
        yourItemsLabel->setScale(0.38f);
        yourItemsLabel->setColor(ccc3(255, 100, 100)); // Tinted reddish for loss feedback
        this->m_mainLayer->addChild(yourItemsLabel);

        auto theirItemsLabel = CCLabelBMFont::create("Receiving: Custom Death Effect [Amethyst Void]", "bigFont.fnt");
        theirItemsLabel->setPosition({ winSize.width / 2, winSize.height / 2 - 45 });
        theirItemsLabel->setScale(0.38f);
        theirItemsLabel->setColor(ccc3(100, 255, 100)); // Tinted green for gain feedback
        this->m_mainLayer->addChild(theirItemsLabel);

        // 5. Build Control Interaction Buttons Menu
        auto menu = CCMenu::create();
        menu->setPosition({ 0, 0 });
        this->m_mainLayer->addChild(menu);

        // --- BUTTON A: MUTUAL CONFIRM LOCK ---
        auto lockSprite = ButtonSprite::create("Lock Offer", 90, true, "bigFont.fnt", "GJ_button_01.png", 25.0f, 0.4f);
        auto lockBtn = CCMenuItemSpriteExtra::create(lockSprite, this, menu_selector(VersusVisualTradeLayer::onLockOffer));
        lockBtn->setPosition({ winSize.width / 2 - 60, winSize.height / 2 - 105 });
        menu->addChild(lockBtn);

        // --- BUTTON B: ABORT TRANSACTION ---
        auto abortSprite = ButtonSprite::create("Cancel", 90, true, "bigFont.fnt", "GJ_button_06.png", 25.0f, 0.4f);
        auto abortBtn = CCMenuItemSpriteExtra::create(abortSprite, this, menu_selector(VersusVisualTradeLayer::onAbort));
        abortBtn->setPosition({ winSize.width / 2 + 60, winSize.height / 2 - 105 });
        menu->addChild(abortBtn);

        return true;
    }

    void onLockOffer(CCObject* sender) {
        FLAlertLayer::create("Trade Protocol", "Offer locked securely! Awaiting friend's dual signature confirmation...", "OK")->show();
    }

    void onAbort(CCObject* sender) {
        removeFromParentAndCleanup(true);
    }
};

