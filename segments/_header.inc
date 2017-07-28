<?php
/**
 * Template header
 *
 * @package    BardCanvas
 * @subpackage MH Magazine Lite Template
 * @author     Alejandro Caballero - lava.caballero@gmail.com
 */

if( $settings->get("templates:mh_magazine_lite.disable_header") == "true" ) return;

$text    = $settings->get("templates:mh_magazine_lite.header_logo_text");
$image   = $settings->get("templates:mh_magazine_lite.header_logo_image");
$bgcolor = $settings->get("templates:mh_magazine_lite.header_background_color");
$links   = $settings->get("templates:mh_magazine_lite.header_links_panel");
$class   = $settings->get("templates:mh_magazine_lite.header_text_style");

if( "{$text}{$image}" == "" ) return;

$links = parse_mhmaglite_links_list($links);
if( empty($bgcolor) ) $bgcolor = "transparent";
?>

<div id="mhmaglite_custom_header" class="<?= $class ?>" style="background-color: <?= $bgcolor ?>;">
    <a class="logo" href="<?= $config->full_root_path ?>/">
        <? if( ! empty($image) ): ?>
            <img class="image" src="<?= $image ?>">
        <? endif; ?>
        
        <? if( ! empty($text) ): ?>
            <span class="caption"><?= $text ?></span>
        <? endif; ?>
    </a>
    
    <? if( ! empty($links) ): ?>
        <div class="links_panel">
            <div class="links"><?= $links ?></div>
            <br clear="left">
        </div>
    <? endif; ?>
</div>
