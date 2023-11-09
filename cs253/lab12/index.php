<?php

# This code came from http://www.virtualventures.ca/~cat/
# Modified by Jack Applin <Applin@ColoState.Edu>

# Directory listings should not be cached:
header('Expires: ' . gmdate('D, d M Y H:i:s T'));
header('Last-Modified: ' . gmdate('D, d M Y H:i:s T'));
header('Cache-Control: no-store, no-cache, must-revalidate');
header('Cache-Control: post-check=0, pre-check=0', false);
header('Pragma: no-cache');

?><!doctype html>
<meta charset='utf-8'>
<title>
    <?= $title='Listing of ' . substr($_SERVER['REQUEST_URI'],1); ?>
</title>
<style type='text/css'>
    h1 {
	margin-top: 0;
    }
    table {
	border: none;
	border-spacing: 0;
	border-collapse: collapse;
    }
    td,th {
	padding: 0 2ex 0 0;
    }
    tr:nth-child(odd) {
	background: #e5e5e5;
    }
    td:nth-child(1) {
	font-family: monospace;	/* mode: drwxr-xr-x */
    }
    th:nth-child(4),td:nth-child(4) {
	text-align: right;	/* size: right-aligned number */
    }
</style>
<h1>
    <?= $title ?>
</h1>
<table>
    <tr>
	<th>Mode
	<th>Owner
	<th>Group
	<th>Size
	<th>Modified
	<th>Name

<?php

$files = scandir('.');		# List of files
natsort($files);		# Sort filenames so foo3 comes before foo12
foreach ($files as $f) {
    # Don’t show dot files (except for ..); don’t show index.php.
    if ($f[0] == '.' && $f != '..' || $f == 'index.php')
	continue;

    $stat = lstat($f);
    echo '<tr>';

    # Mode
    $m = $stat['mode'];
    echo '<td>';
    echo is_link($f) ? 'l' : (is_dir($f) ? 'd' : (is_file($f) ? '-' : '?'));

    $s = 'rwxrwxrwx';
    if ($m & 04000) $s[2] = 's';
    if ($m & 02000) $s[5] = 's';
    if ($m & 01000) $s[8] = 't';
    $map = ['r'=>'-', 'w'=>'-', 'x'=>'-', 's'=>'S', 't'=>'T'];
    for ($bit=0; $bit<9; $bit++)
	echo $m & (0400 >> $bit) ? $s[$bit] : $map[$s[$bit]];

    $u = posix_getpwuid($stat['uid']);
    $g = posix_getgrgid($stat['gid']);

    echo '<td>', $u ? $u['name'] : $stat['uid'],
         '<td>', $g ? $g['name'] : $stat['gid'];

    if (is_dir($f) || is_link($f))	    # Directory or link?
	echo '<td>&nbsp;';		    # Size is irrelevant for them.
    else
	echo "<td>$stat[size]";		    # Plain file: show the size

    echo '<td>', date('Y‒m‒d H:i:s', $stat['mtime']),
         '<td>';

    $encf = htmlentities($f, ENT_QUOTES, 'UTF-8');
    # Link to world-readable files, but can still execute unreadable .php files.
    if (($stat['mode'] & 0444) == 0444 || preg_match('/\.php$/', $f))
	 # Directory links have trailing slash to avoid redirection:
	echo "<a href='$encf", (is_dir($f) ? '/' : ''), "'>$encf</a>";
    else
	echo $encf;

    if (is_link($f))
	echo ' &rarr; ', readlink($f);

    echo "\n";
}
?>
</table>
