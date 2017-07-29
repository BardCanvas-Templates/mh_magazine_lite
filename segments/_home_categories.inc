<?php
/**
 * Per-category posts listing
 *
 * @package    BardCanvas
 * @subpackage MH Magazine Lite Template
 * @author     Alejandro Caballero - lava.caballero@gmail.com
 *
 * @var template    $template
 * @var post_record $post
 */

use hng2_base\template;
use hng2_modules\categories\categories_repository;
use hng2_modules\categories\category_record;
use hng2_modules\posts\post_record;
use hng2_templates\mh_magazine_lite\posts_repository_extender;

if( ! empty($_GET["offset"]) ) return;

$categories_repository = new categories_repository();
$categories_filter     = array("visibility = 'public'");
$exclusive_slugs       = $settings->get("templates:mh_magazine_lite.per_category_slugs");
if( ! empty($exclusive_slugs) )
{
    $sanitized_list = array();
    foreach(explode("\n", $exclusive_slugs) as $line)
    {
        $line = trim($line);
        if( substr($line, 0, 1) == "#" ) continue;
        
        $sanitized_list[] = "'$line'";
    }
    
    $sanitized_list      = implode(", ", $sanitized_list);
    $categories_filter[] = "slug in ($sanitized_list)";
}

$categories = $categories_repository->find($categories_filter, 0, 0, "title asc");
if( empty($categories) ) return;

/** @var category_record[] $categories_by_id */
$categories_by_id = array();
foreach($categories as $category) $categories_by_id[$category->id_category] = $category;

$repository = new posts_repository_extender();
$posts      = $repository->get_for_template_listing($categories);
if( empty($posts) ) return;
?>
<div id="per_category_index" class="posts_index clearfix">
    
    <? foreach($posts as $category_id => $list):
        $category = $categories_by_id[$category_id];
        ?><div class="listing_container">
            <h2><a href="<?= $config->full_root_path ?>/category/<?= $category->slug ?>"><?= $category->title ?></a></h2>
            <div class="listing">
                <? foreach($list as $post):
                    $class = empty($post->featured_image_thumbnail) ? "no_image" : "clearfix";
                    ?>
                    <div class="post <?= $class ?>">
                        <?
                        if( ! empty($post->featured_image_thumbnail) ):
                            ?><a class="post_featured_image thumbnail <?= $post->featured_media_type ?>"
                               href="<?= $post->get_permalink() ?>"
                               style="background-image: url('<?= $post->featured_image_thumbnail ?>');"><img
                               src="<?= $config->full_root_path ?>/media/spacer.png"></a><?
                        endif;
                        
                        ?><div class="details">
                            <h3><a href="<?= $post->get_permalink() ?>"><?= $post->title ?></a></h3>
                            <span class="nowrap">
                                <i class="fa fa-calendar"></i>
                                <?= time_complete_string($post->publishing_date) ?>
                            </span>
                            <? if($post->comments_count > 0): ?>
                                <span class="nowrap">
                                    <i class="fa fa-comment-o"></i>
                                    <?= $post->comments_count ?>
                                </span>
                            <? endif; ?>
                        </div>
                    </div>
                <? endforeach; ?>
            </div>
        </div><?
    endforeach; ?>
</div>
