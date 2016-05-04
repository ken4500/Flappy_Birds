<GameFile>
  <PropertyGroup Name="TitleScene" Type="Scene" ID="be3027f0-ca91-4511-861f-cd16a76e5d93" Version="3.10.0.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="0" Speed="1.0000" />
      <AnimationList>
        <AnimationInfo Name="default" StartIndex="0" EndIndex="0">
          <RenderColor A="255" R="255" G="20" B="147" />
        </AnimationInfo>
      </AnimationList>
      <ObjectData Name="Scene" ctype="GameNodeObjectData">
        <Size X="288.0000" Y="512.0000" />
        <Children>
          <AbstractNodeData Name="back" ActionTag="1355614818" Tag="4" IconVisible="False" PositionPercentXEnabled="True" ctype="SpriteObjectData">
            <Size X="288.0000" Y="512.0000" />
            <Children>
              <AbstractNodeData Name="character" ActionTag="509196833" Tag="9" IconVisible="True" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="144.0000" RightMargin="144.0000" TopMargin="220.9739" BottomMargin="291.0261" StretchWidthEnable="False" StretchHeightEnable="False" InnerActionSpeed="1.0000" CustomSizeEnabled="False" ctype="ProjectNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <AnchorPoint />
                <Position X="144.0000" Y="291.0261" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.5000" Y="0.5684" />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="Normal" Path="Character.csd" Plist="" />
              </AbstractNodeData>
              <AbstractNodeData Name="ground" ActionTag="-678811382" Tag="21" IconVisible="True" RightMargin="288.0000" TopMargin="400.0000" BottomMargin="112.0000" StretchWidthEnable="False" StretchHeightEnable="False" InnerActionSpeed="1.0000" CustomSizeEnabled="False" ctype="ProjectNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <AnchorPoint />
                <Position Y="112.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition Y="0.2188" />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="Normal" Path="Ground.csd" Plist="" />
              </AbstractNodeData>
            </Children>
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="144.0000" Y="256.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.5000" Y="0.5000" />
            <PreSize X="1.0000" Y="1.0000" />
            <FileData Type="Normal" Path="Assets/background/back1.png" Plist="" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
          <AbstractNodeData Name="playButton" ActionTag="-767463754" Tag="49" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="19.7600" RightMargin="152.2400" TopMargin="341.9998" BottomMargin="100.0002" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="86" Scale9Height="48" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
            <Size X="116.0000" Y="70.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="77.7600" Y="135.0002" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.2700" Y="0.2637" />
            <PreSize X="0.4028" Y="0.1367" />
            <TextColor A="255" R="65" G="65" B="70" />
            <DisabledFileData Type="Default" Path="Default/Button_Disable.png" Plist="" />
            <PressedFileData Type="Normal" Path="Assets/UI/btn_play.png" Plist="" />
            <NormalFileData Type="Normal" Path="Assets/UI/btn_play.png" Plist="" />
            <OutlineColor A="255" R="255" G="0" B="0" />
            <ShadowColor A="255" R="110" G="110" B="110" />
          </AbstractNodeData>
          <AbstractNodeData Name="leaderboardButton" ActionTag="1432896965" Tag="50" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="152.2400" RightMargin="19.7600" TopMargin="340.9998" BottomMargin="101.0002" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="86" Scale9Height="48" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
            <Size X="116.0000" Y="70.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="210.2400" Y="136.0002" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.7300" Y="0.2656" />
            <PreSize X="0.4028" Y="0.1367" />
            <TextColor A="255" R="65" G="65" B="70" />
            <DisabledFileData Type="Default" Path="Default/Button_Disable.png" Plist="" />
            <PressedFileData Type="Normal" Path="Assets/UI/leaderboard.png" Plist="" />
            <NormalFileData Type="Normal" Path="Assets/UI/leaderboard.png" Plist="" />
            <OutlineColor A="255" R="255" G="0" B="0" />
            <ShadowColor A="255" R="110" G="110" B="110" />
          </AbstractNodeData>
          <AbstractNodeData Name="logoFlappyBird" ActionTag="-338353557" Tag="78" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="55.0000" RightMargin="55.0000" TopMargin="141.5099" BottomMargin="322.4901" ctype="SpriteObjectData">
            <Size X="178.0000" Y="48.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="144.0000" Y="346.4901" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.5000" Y="0.6767" />
            <PreSize X="0.6181" Y="0.0938" />
            <FileData Type="Normal" Path="Assets/logo/logo_flappy_bird.png" Plist="" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
          <AbstractNodeData Name="rateButton" ActionTag="1876698211" Tag="79" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="107.0000" RightMargin="107.0000" TopMargin="276.1917" BottomMargin="187.8083" ctype="SpriteObjectData">
            <Size X="74.0000" Y="48.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="144.0000" Y="211.8083" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.5000" Y="0.4137" />
            <PreSize X="0.2569" Y="0.0938" />
            <FileData Type="Normal" Path="Assets/UI/btn_rate.png" Plist="" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
        </Children>
      </ObjectData>
    </Content>
  </Content>
</GameFile>