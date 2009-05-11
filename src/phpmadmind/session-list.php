<h2>[master]/session-list</h2>
<?php
$info = simplexml_load_string($m->list_sessions());
if ($info) {
?>
<div class="content-layer">
  <table>
  <?php $x=1; foreach ($info->session as $s) { ?>
    <tr<?=$x=!$x?" class=\"odd\"":""?>>
      <td class="session"> <strong><a class="id" href="?p=session-info&amp;id=<?=$s->attributes()->id?>">session #<?=$s->attributes()->id?></a></strong> </td>
      <td><?=$s->latest?></td>
      <td class="state"><?=$s->state?></td>
      <td class="url-info"><?=$s->crawler." &lt;- <span class=\"input\">".$s->input."</span>"?></td>
      <td>client: <a class="id" href="?p=client-info&amp;id=<?=$s->client?>"><?=substr($s->client, 0, 3)."...".substr($s->client, -3)?></a></td>
    </tr>
  <?php } ?>
  </table>
</div>
<?php
} else {
    echo "<em>No sessions found.</em>";
}
?>
