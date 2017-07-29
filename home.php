<?
/**
 * Home layout
 *
 * @package    BardCanvas
 * @subpackage MH Magazine Lite Template
 * @author     Alejandro Caballero - lava.caballero@gmail.com
 *             
 * @var template $template
 * @var settings $settings
 * @var config   $config
 * @var account  $account
 */

use hng2_base\account;
use hng2_base\config;
use hng2_base\settings;
use hng2_base\template;
use hng2_tools\internals;

include __DIR__ . "/functions.inc";
$template->init(__FILE__);
$template->set("page_tag", "home"); # This is a very specific case
$account->ping();

foreach($template->get_includes("pre_rendering") as $module => $include)
{
    $this_module = $modules[$module];
    include "{$this_module->abspath}/contents/{$include}";
}

if( $template->get("no_right_sidebar") ) $template->clear_right_sidebar_items();

header("Content-Type: text/html; charset=utf-8"); ?>
<!DOCTYPE html>
<html>
<head>
    <!--suppress CssInvalidPropertyValue -->
    <style type="text/css">@-ms-viewport{ width: device-width; }</style>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <? $template->set("include_notification_functions", true); ?>
    <? $template->set("jquery_ui_theme", "redmond"); ?>
    <? include ROOTPATH . "/includes/common_header.inc" ?>
    
    <!-- This template -->
    <link rel="stylesheet" type="text/css" href="<?= $template->url ?>/media/styles~v<?=time()?>.css">
    <link rel="stylesheet" type="text/css" href="<?= $template->url ?>/media/post_styles~v<?=time()?>.css">
    <link rel="stylesheet" type="text/css" href="<?= $template->url ?>/media/colors~v<?=time()?>.css">
    <link rel="stylesheet" type="text/css" href="<?= $template->url ?>/media/extras~v<?=time()?>.css">
    
    <? if( $template->count_right_sidebar_items() > 0 ): ?>
        <!-- Right sidebar -->
        <link rel="stylesheet" type="text/css" href="<?= $template->url ?>/media/right_sidebar_addon~v<?=time()?>.css">
    <? endif; ?>
    
    <!-- Always-on -->
    <? $template->render_always_on_files(); ?>
    
    <!-- Per module loads -->
    <?
    foreach($template->get_includes("html_head") as $module => $include)
    {
        $this_module = $modules[$module];
        include "{$this_module->abspath}/contents/{$include}";
    }
    ?>
</head>
<body data-orientation="landscape" data-viewport-class="0" <?=$template->get("additional_body_attributes")?>
      data-page-tag="<?= $template->get("page_tag") ?>" class="home"
      data-is-mobile="<?= is_mobile() ? "true" : "false" ?>"
      data-is-known-user="<?= $account->_exists ? "true" : "false" ?>"
      data-user-slug="<?= $account->user_name ?>"
      data-user-level="<?= $account->level ?>"
      style="<?= build_mhmaglite_body_style() ?>">

<div id="body_wrapper">
    
    <?
    foreach($template->get_includes("pre_header") as $module => $include)
    {
        $this_module = $modules[$module];
        include "{$this_module->abspath}/contents/{$include}";
    }
    ?>
    
    <div id="header">
        
        <div class="header_top">
            <?
            if( $settings->get("engine.show_admin_menu_in_header_menu") != "true" )
                include "{$template->abspath}/segments/admin_menu.inc";
            
            foreach($template->get_includes("header_top") as $module => $include)
            {
                $this_module = $modules[$module];
                include "{$this_module->abspath}/contents/{$include}";
            }
            
            include __DIR__ . "/segments/_header.inc";
            ?>
        </div>
        
        <div class="menu clearfix">
            
            <span id="main_menu_trigger" class="main_menu_item" onclick="toggle_main_menu_items()">
                <span class="fa fa-bars fa-fw"></span>
            </span>
            
            <a id="home_menu_button" class="main_menu_item current always_visible pull-left" href="<?= $config->full_root_path ?>/">
                <?= $template->language->home ?>
            </a>
            
            <?
            if( $settings->get("engine.show_admin_menu_in_header_menu") == "true" )
                add_admin_menu_items_to_header_menu();
            
            foreach($template->get_includes("header_menu") as $module => $include)
            {
                $this_module = $modules[$module];
                include "{$this_module->abspath}/contents/{$include}";
            }
            
            echo $template->build_menu_items("priority");
            ?>
        </div>
        
        <div class="header_bottom">
            <?
            foreach($template->get_includes("header_bottom") as $module => $include)
            {
                $this_module = $modules[$module];
                include "{$this_module->abspath}/contents/{$include}";
            }
            ?>
        </div>
        
    </div><!-- /#header -->
    
    <?
    foreach($template->get_includes("pre_content") as $module => $include)
    {
        $this_module = $modules[$module];
        include "{$this_module->abspath}/contents/{$include}";
    }
    ?>
    
    <div id="content_wrapper" class="clearfix">
        
        <div id="content">
            <?
            foreach($template->get_includes("content_top") as $module => $include)
            {
                $this_module = $modules[$module];
                include "{$this_module->abspath}/contents/{$include}";
            }
            
            if( $settings->get("templates:mh_magazine_lite.listing_selection") == "" )
                $config->globals["modules:posts.avoid_preloading_posts_for_home_index"] = true;
            
            foreach($template->get_includes("home_content") as $module => $include)
            {
                $this_module = $modules[$module];
                include "{$this_module->abspath}/contents/{$include}";
            }
            
            foreach($template->get_includes("content_bottom") as $module => $include)
            {
                $this_module = $modules[$module];
                include "{$this_module->abspath}/contents/{$include}";
            }
            ?>
        </div><!-- /#content -->
        
        <? if( $template->count_right_sidebar_items() > 0 ): ?>
            <div id="right_sidebar" class="sidebar">
                <? echo $template->build_right_sidebar_items(); ?>
            </div>
        <? endif; ?>
        
    </div>
        
    <?
    foreach($template->get_includes("pre_footer") as $module => $include)
    {
        $this_module = $modules[$module];
        include "{$this_module->abspath}/contents/{$include}";
    }
    ?>
    
    <div id="footer">
        <?
        foreach($template->get_includes("footer_top") as $module => $include)
        {
            $this_module = $modules[$module];
            include "{$this_module->abspath}/contents/{$include}";
        }
        
        include __DIR__ . "/segments/_footer.inc";
        
        $footer_contents = $template->get("footer_contents");
        if( empty($footer_contents) ) $footer_contents = '
            <div class="footer_contents" align="center">
                {$website_name}
                {$powered_by}
                •
                {$query_tracking_info}
                {$timing_info}
                {$memory_info}
                {$internals_link}
            </div>
        ';
        echo replace_escaped_objects($footer_contents, array(
            '{$website_name}'        => $settings->get("engine.website_name"),
            '{$powered_by}'          => replace_escaped_vars($language->powered_by, '{$version}', $config->engine_version),
            '{$query_tracking_info}' => $config->query_tracking_enabled ? ("<span class='fa fa-database fa-fw'></span>" . number_format($database->get_tracked_queries_count()) . " • ") : "",
            '{$timing_info}'         => "<span class='fa fa-clock-o fa-fw'></span>" . number_format(microtime(true) - $global_start_time, 3) . "s • ",
            '{$memory_info}'         => "<span class='fa fa-tachometer fa-fw'></span>" . number_format(memory_get_usage(true) / 1024 / 1024, 1) . "MiB ",
            '{$internals_link}'      => $config->display_performance_details && EMBED_INTERNALS ? " • <span class=\"fa fa-plus fa-fw pseudo_link\" onclick=\"$('.internals').show();\"></span>" : "",
        ));
        
        foreach($template->get_includes("footer_bottom") as $module => $include)
        {
            $this_module = $modules[$module];
            include "{$this_module->abspath}/contents/{$include}";
        }
        ?>
        
    </div><!-- /#footer -->
    
    <?
    foreach($template->get_includes("post_footer") as $module => $include)
    {
        $this_module = $modules[$module];
        include "{$this_module->abspath}/contents/{$include}";
    }
    ?>
    
</div><!-- /#body_wrapper -->

<!-- These must be at the end of the document -->
<script type="text/javascript" src="<?= $config->full_root_path ?>/lib/tinymce-4.6.3/tinymce.min.js"></script>
<? $template->render_tinymce_additions(); ?>
<script type="text/javascript" src="<?= $config->full_root_path ?>/media/init_tinymce~v<?=$config->engine_version?>.js"></script>
<script type="text/javascript">
    $(document).ready(function()
    {
        tinymce.init(tinymce_defaults);
        tinymce.init(tinymce_full_defaults);
        tinymce.init(tinymce_minimal_defaults);
    });
</script>

<?
foreach($template->get_includes("pre_eof") as $module => $include)
{
    $this_module = $modules[$module];
    include "{$this_module->abspath}/contents/{$include}";
}

internals::render(__FILE__);
?>

</body>
</html>
<?
foreach($template->get_includes("post_rendering") as $module => $include)
{
    $this_module = $modules[$module];
    include "{$this_module->abspath}/contents/{$include}";
}
?>
