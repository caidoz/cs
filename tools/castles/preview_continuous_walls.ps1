$ErrorActionPreference='Stop'
Add-Type -AssemblyName System.Drawing
$root=(Resolve-Path .).Path
$resource=Join-Path $root 'Resources/res'
function Paint($g,$relative,$x,$y,$w,$h) {
    $path=Join-Path $resource $relative
    $img=[System.Drawing.Image]::FromFile($path)
    try { $g.DrawImage($img,[single]$x,[single]$y,[single]$w,[single]$h) }
    finally { $img.Dispose() }
}
function Preview($castle,$stage,$scale) {
    $cw=700; $ch=1050
    $canvas=[System.Drawing.Bitmap]::new($cw,$ch)
    $g=[System.Drawing.Graphics]::FromImage($canvas)
    try {
        $g.Clear([System.Drawing.Color]::FromArgb(23,42,50))
        $g.InterpolationMode=[System.Drawing.Drawing2D.InterpolationMode]::HighQualityBicubic
        $g.PixelOffsetMode=[System.Drawing.Drawing2D.PixelOffsetMode]::HighQuality
        $wallH=$castle*128
        $upper=@{2=220;3=197;4=340;5=300;6=320;7=320;8=320;9=320;10=330}[$castle]
        $leftW=140+12*$castle; $rightW=110+10*$castle
        $roomLeft=($cw-512*$scale)/2; $bottom=$ch-130
        $prefix=('castle_exterior/castle_{0:00}' -f $castle)
        Paint $g "$prefix`_combat_deck_stage_$stage.png" ($roomLeft-112*$scale) $bottom (736*$scale) (144*$scale)
        # Match CastleModularDebug.h: hide alpha padding at the room/wall seam.
        $seamColors=@{2='716B63';3='864736';4='B7AA8D';5='47786D';6='4C3D3B';7='A0C6D5';8='655078';9='494047';10='CDBF9D'}
        $seamBrush=[Drawing.SolidBrush]::new([Drawing.ColorTranslator]::FromHtml('#'+$seamColors[$castle]))
        try {
            $outer=[math]::Ceiling(32*$scale);$inner=[math]::Ceiling(20*$scale)
            $roomRight=$roomLeft+512*$scale
            $g.FillRectangle($seamBrush,[single]($roomLeft-$outer),[single]($bottom-$wallH*$scale),[single]($outer+$inner),[single]($wallH*$scale))
            $g.FillRectangle($seamBrush,[single]($roomRight-$inner),[single]($bottom-$wallH*$scale),[single]($outer+$inner),[single]($wallH*$scale))
        } finally { $seamBrush.Dispose() }
        for($floor=1;$floor -le $castle;$floor++) {
            $roomStage=if($floor -eq $castle){$stage}else{5}
            Paint $g ('castle_room_{0:00}_{1}.png' -f $floor,$roomStage) $roomLeft ($bottom-$floor*128*$scale) (512*$scale) (128*$scale)
        }
        $lower=[math]::Min(1024,$wallH)
        Paint $g "$prefix`_wall_left_stage_$stage`_lower.png" ($roomLeft-$leftW*$scale) ($bottom-$lower*$scale) ($leftW*$scale) ($lower*$scale)
        Paint $g "$prefix`_wall_right_stage_$stage`_lower.png" ($roomLeft+512*$scale) ($bottom-$lower*$scale) ($rightW*$scale) ($lower*$scale)
        if($wallH -gt 1024) {
            $rest=$wallH-1024
            Paint $g "$prefix`_wall_left_stage_$stage`_upper.png" ($roomLeft-$leftW*$scale) ($bottom-$wallH*$scale) ($leftW*$scale) ($rest*$scale)
            Paint $g "$prefix`_wall_right_stage_$stage`_upper.png" ($roomLeft+512*$scale) ($bottom-$wallH*$scale) ($rightW*$scale) ($rest*$scale)
        }
        Paint $g "$prefix`_roof_stage_$stage.png" ($roomLeft-64*$scale) ($bottom-($wallH+$upper)*$scale) (640*$scale) ($upper*$scale)
        Paint $g "$prefix`_command_platform_stage_$stage.png" ($roomLeft+480*$scale) ($bottom-128*$scale) (192*$scale) (128*$scale)
        $grow=(1+.135*($castle-1))*(.82+.036*$stage)
        Paint $g "$prefix`_heavy_cannon_stage_$stage.png" ($roomLeft+544*$scale) ($bottom-(128+($grow-1)*64)*$scale) (128*$grow*$scale) (64*$grow*$scale)
        $out=Join-Path $root ('tools/castles/preview_wall_castle_{0:00}_stage_{1}.png' -f $castle,$stage)
        $canvas.Save($out,[System.Drawing.Imaging.ImageFormat]::Png)
        Write-Output $out
    } finally { $g.Dispose();$canvas.Dispose() }
}
foreach($stage in 0..5) {
    Preview 2 $stage .80
    Preview 3 $stage .75
    Preview 10 $stage .49
}
Preview 4 0 .70
Preview 4 5 .70
