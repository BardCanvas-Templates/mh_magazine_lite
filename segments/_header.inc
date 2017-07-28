<?php
/**
 * Template header
 *
 * @package    BardCanvas
 * @subpackage MH Magazine Lite Template
 * @author     Alejandro Caballero - lava.caballero@gmail.com
 */

if( $settings->get("templates:mh_magazine_lite.disable_header") == "true" ) return;

$text  = $settings->get("templates:mh_magazine_lite.header_logo_text");
$image = $settings->get("templates:mh_magazine_lite.header_logo_image");
$links = $settings->get("templates:mh_magazine_lite.header_links_panel");

if( "{$text}{$image}" == "" ) return;

$class = empty($links) ? "" : "clearfix";
$links = parse_mhmaglite_links_list($links);
?>

<div id="mhmaglite_custom_header" class="<?= $class ?>">
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
        </div>
    <? endif; ?>
</div>
