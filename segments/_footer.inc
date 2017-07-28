<?php
/**
 * Template footer
 *
 * @package    BardCanvas
 * @subpackage MH Magazine Lite Template
 * @author     Alejandro Caballero - lava.caballero@gmail.com
 */

if( $settings->get("templates:mh_magazine_lite.disable_footer") == "true" ) return;

$s1 = $settings->get("templates:mh_magazine_lite.footer_section1");
$s2 = $settings->get("templates:mh_magazine_lite.footer_section2");
$s3 = $settings->get("templates:mh_magazine_lite.footer_section3");
$rl = $settings->get("templates:mh_magazine_lite.footer_links_row_left");
$rr = $settings->get("templates:mh_magazine_lite.footer_links_row_right");
$fr = $settings->get("templates:mh_magazine_lite.footer_final_row");

$sections = array();

$frames = array();
if( ! empty($s1) ) $frames[] = $s1;
if( ! empty($s2) ) $frames[] = $s2;
if( ! empty($s3) ) $frames[] = $s3;
if( ! empty($frames) )
{
    if(count($frames) == 1)
    {
        list($title, $content) = separate_mhmaglite_footer_section($frames[0]);
        $content = parse_mhmaglite_links_list($content, true);
        
        $sections[] = "
            <div class='mhmaglite_footer row1'>
                <div class='content_frame'>
                    <h3>$title</h3>
                    <div>$content</div>
                </div>
            </div>
        ";
    }
    else
    {
        $count  = count($frames);
        $markup = "<div class='mhmaglite_footer row1 multicol cols-{$count}'>";
        foreach($frames as $index => $frame)
        {
            $class = $count == 3 && $index == 0 ? "biggest-col" : "";
            
            list($title, $content) = separate_mhmaglite_footer_section($frame);
            $content = parse_mhmaglite_links_list($content, true);
            
            $markup .= "
                <div class='content_frame col {$class}'>
                    <h3>$title</h3>
                    <div>$content</div>
                </div>
            ";
        }
        $markup .= "</div>";
        $sections[] = $markup;
    }
}

if( "{$rl}{$rr}" != "" )
{
    $dclass = "";
    if(       empty($rl) && ! empty($rr) ) $dclass = "alignright";
    elseif( ! empty($rl) && ! empty($rr) ) $dclass = "clearfix";
    
    $markup = "<div class='mhmaglite_footer row2'><div class='content_frame $dclass'>";
    
    if( ! empty($rl) ) $markup .= "<div class='panel left'>" . parse_mhmaglite_links_list($rl) . "</div>";
    if( ! empty($rr) ) $markup .= "<div class='panel right'>" . parse_mhmaglite_links_list($rr) . "</div>";
    
    $markup .= "</div></div>";
    
    $sections[] = $markup;
}

if( ! empty($fr) )
{
    list($title, $content) = separate_mhmaglite_footer_section($fr);
    
    $sections[] = "
        <div class='mhmaglite_footer row3'>
            <div class='content_frame'>
                <h3>$title</h3>
                <p>$content</p>
            </div>
        </div>
    ";
}

echo implode("\n", $sections);
