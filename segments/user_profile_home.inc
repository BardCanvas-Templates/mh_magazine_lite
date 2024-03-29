<?php
/**
 * User profile home contents
 *
 * @package    BardCanvas
 * @subpackage MH Magazine Lite Template
 * @author     Alejandro Caballero - lava.caballero@gmail.com
 *
 * @var module            $current_module accounts
 * @var account           $account
 * @var config            $config
 * @var template          $template
 * @var \SimpleXMLElement $language
 * @var settings          $settings
 */

use hng2_base\account;
use hng2_base\config;
use hng2_base\module;
use hng2_base\settings;
use hng2_base\template;

/** @var account $author */
$author = $template->get("user_profile_account");
?>

<h1><?= replace_escaped_vars($current_module->language->user_profile_page->title, '{$user}', $author->get_processed_display_name()) ?></h1>

<div id="user_info_sections">
    
    <section>
        <h2><?= $current_module->language->user_profile_page->info->title ?></h2>
        <form class="framed_content">
            <div class="field">
                <div class="caption">
                    <?= $current_module->language->user_profile_page->info->level ?>
                </div>
                <div class="input">
                    <?= $author->level ?> (<?= $config->user_levels_by_level[$author->level] ?>)
                </div>
            </div>
            <div class="field">
                <div class="caption">
                    <?= $current_module->language->user_profile_page->info->member_since ?>
                </div>
                <div class="input">
                    <?= time_complete_string($author->creation_date) . " (" . time_elapsed_string($author->creation_date) .")" ?>
                </div>
            </div>
            <?
            $last_seen = $author->get_last_activity();
            if( ! empty($last_seen) ): ?>
                <div class="field">
                    <div class="caption">
                        <?= $current_module->language->user_profile_page->info->last_seen ?>
                    </div>
                    <div class="input">
                        <?= $author->get_last_activity(true) ?>
                    </div>
                </div>
            <? endif; ?>
            <div class="field">
                <div class="caption">
                    <?= $current_module->language->user_profile_page->info->country ?>
                </div>
                <div class="input">
                    <?= $author->country_name ?>
                </div>
            </div>
            <? if( ! empty($author->homepage_url) ): ?>
                <div class="field">
                    <div class="caption">
                        <?= $current_module->language->user_profile_page->info->home_page ?>
                    </div>
                    <div class="input">
                        <a href="<?= $author->homepage_url ?>" target="_blank"><?= $author->homepage_url ?></a>
                    </div>
                </div>
            <? endif; ?>
            <div class="field">
                <div class="caption">
                    <?= $current_module->language->user_profile_page->info->feed ?>
                </div>
                <div class="input">
                    <a href="<?= $config->full_root_url ?>/user/<?= $author->user_name ?>/feed" target="_blank">
                        <?= $config->full_root_url ?>/user/<?= $author->user_name ?>/feed
                    </a>
                </div>
            </div>
        </form>
    </section>
    
    <? if( ! empty($author->signature) ): ?>
        <section>
            <h2><?= $current_module->language->user_profile_page->signature->title ?></h2>
            <div class="framed_content user_signature">
                <?= $author->get_processed_signature() ?>
            </div>
        </section>
    <? endif; ?>
    
    <? if( ! empty($author->bio) ): ?>
        <section>
            <h2><?= $current_module->language->user_profile_page->bio->title ?></h2>
            <div class="framed_content user_bio">
                <?= $author->bio ?>
            </div>
        </section>
    <? endif; ?>
    
    <? if( $author->id_account != $account->id_account
           && ($modules["contact"]->enabled || $modules["messaging"]->enabled) ): ?>
        <?
        $items = array();
        
        if( $modules["messaging"]->enabled )
        {
            $caption = replace_escaped_vars( $language->contact->pm->title, '{$website_name}', $settings->get("engine.website_name") );
            $link    = $author->get_pm_sending_link($caption, "pseudo_link", "white-space: normal");
            if( ! empty($link) ) $items[] = $link;
        }
        
        if( $modules["contact"]->enabled )
        {
            if( $account->_exists || $settings->get("modules:contact.no_anonymous_emails") != "true" )
            {
                if(
                    $author->get_engine_pref("@contact:allow_emails") != "false" ||
                    $account->level >= config::MODERATOR_USER_LEVEL
                ) {
                    $aun = urlencode($author->user_name);
                    $items[] = "
                        <a href='{$config->full_root_path}/contact/?target={$aun}'>
                            <span class='fa fa-envelope'></span>
                            {$language->contact->email->title}
                        </a>
                    ";
                }
            }
        }
        ?>
        <? if( ! empty($items) ): ?>
            <section>
                <h2><?= replace_escaped_vars($language->contact->contact_user, '{$display_name}', $author->get_processed_display_name()) ?></h2>
                <div class="framed_content">
                    <ul>
                        <? foreach($items as $item) echo "<li>$item</li>"; ?>
                    </ul>
                </div>
            </section>
        <? endif; ?>
    <? endif; ?>
    
    <? $current_module->load_extensions("user_profile_home", "additional_sections"); ?>
    
</div>
