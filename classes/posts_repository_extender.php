<?php
namespace hng2_templates\mh_magazine_lite;

use hng2_modules\categories\category_record;
use hng2_modules\posts\post_record;
use hng2_modules\posts\posts_data;
use hng2_modules\posts\posts_repository;

class posts_repository_extender extends posts_repository
{
    /**
     * @param category_record[] $categories
     * 
     * @return post_record[][]
     */
    function get_for_template_listing($categories)
    {
        global $settings, $database;
        
        if( empty($categories) ) return array();
        
        $today  = date("Y-m-d H:i:s");
        $limit  = $settings->get("templates:mh_magazine_lite.per_category_limit"); if( empty($limit) ) $limit = 3;
        $querys = array();
        $fields = implode(",\n                  ", array_merge(
            array("`{$this->table_name}`.*"),
            $this->additional_select_fields
        ));
        
        foreach($categories as $category)
        {
            $querys[] = "(
                select
                    $fields
                from
                    `{$this->table_name}`
                where status           = 'published'
                and   visibility       = 'public'
                and   publishing_date <= '$today'
                and   main_category    = '{$category->id_category}'
                and   (expiration_date = '0000-00-00 00:00:00' or expiration_date > '$today' )
                order by publishing_date desc
                limit $limit
            )";
        }
        
        $query = implode("\nunion\n", $querys);
        # echo "<pre>$query</pre>";
        $this->last_query = $query;
        
        $res   = $database->query($query);
        if( $database->num_rows($res) == 0 ) return array();
        
        $posts_data = new posts_data();
        while($row = $database->fetch_object($res))
            $posts_data->posts[] = new post_record($row);
        
        $this->preload_authors($posts_data);
        
        $return = array();
        foreach($posts_data->posts as $post)
            $return[$post->main_category][$post->id_post] = $post;
        
        return $return;
    }
}
