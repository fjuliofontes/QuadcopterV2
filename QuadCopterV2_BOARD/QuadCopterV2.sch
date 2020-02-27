<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE eagle SYSTEM "eagle.dtd">
<eagle version="9.5.2">
<drawing>
<settings>
<setting alwaysvectorfont="no"/>
<setting verticaltext="up"/>
</settings>
<grid distance="0.1" unitdist="inch" unit="inch" style="lines" multiple="1" display="no" altdistance="0.01" altunitdist="inch" altunit="inch"/>
<layers>
<layer number="1" name="Top" color="4" fill="1" visible="no" active="no"/>
<layer number="16" name="Bottom" color="1" fill="1" visible="no" active="no"/>
<layer number="17" name="Pads" color="2" fill="1" visible="no" active="no"/>
<layer number="18" name="Vias" color="2" fill="1" visible="no" active="no"/>
<layer number="19" name="Unrouted" color="6" fill="1" visible="no" active="no"/>
<layer number="20" name="Dimension" color="15" fill="1" visible="no" active="no"/>
<layer number="21" name="tPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="22" name="bPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="23" name="tOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="24" name="bOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="25" name="tNames" color="7" fill="1" visible="no" active="no"/>
<layer number="26" name="bNames" color="7" fill="1" visible="no" active="no"/>
<layer number="27" name="tValues" color="7" fill="1" visible="no" active="no"/>
<layer number="28" name="bValues" color="7" fill="1" visible="no" active="no"/>
<layer number="29" name="tStop" color="7" fill="3" visible="no" active="no"/>
<layer number="30" name="bStop" color="7" fill="6" visible="no" active="no"/>
<layer number="31" name="tCream" color="7" fill="4" visible="no" active="no"/>
<layer number="32" name="bCream" color="7" fill="5" visible="no" active="no"/>
<layer number="33" name="tFinish" color="6" fill="3" visible="no" active="no"/>
<layer number="34" name="bFinish" color="6" fill="6" visible="no" active="no"/>
<layer number="35" name="tGlue" color="7" fill="4" visible="no" active="no"/>
<layer number="36" name="bGlue" color="7" fill="5" visible="no" active="no"/>
<layer number="37" name="tTest" color="7" fill="1" visible="no" active="no"/>
<layer number="38" name="bTest" color="7" fill="1" visible="no" active="no"/>
<layer number="39" name="tKeepout" color="4" fill="11" visible="no" active="no"/>
<layer number="40" name="bKeepout" color="1" fill="11" visible="no" active="no"/>
<layer number="41" name="tRestrict" color="4" fill="10" visible="no" active="no"/>
<layer number="42" name="bRestrict" color="1" fill="10" visible="no" active="no"/>
<layer number="43" name="vRestrict" color="2" fill="10" visible="no" active="no"/>
<layer number="44" name="Drills" color="7" fill="1" visible="no" active="no"/>
<layer number="45" name="Holes" color="7" fill="1" visible="no" active="no"/>
<layer number="46" name="Milling" color="3" fill="1" visible="no" active="no"/>
<layer number="47" name="Measures" color="7" fill="1" visible="no" active="no"/>
<layer number="48" name="Document" color="7" fill="1" visible="no" active="no"/>
<layer number="49" name="Reference" color="7" fill="1" visible="no" active="no"/>
<layer number="51" name="tDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="52" name="bDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="88" name="SimResults" color="9" fill="1" visible="yes" active="yes"/>
<layer number="89" name="SimProbes" color="9" fill="1" visible="yes" active="yes"/>
<layer number="90" name="Modules" color="5" fill="1" visible="yes" active="yes"/>
<layer number="91" name="Nets" color="2" fill="1" visible="yes" active="yes"/>
<layer number="92" name="Busses" color="1" fill="1" visible="yes" active="yes"/>
<layer number="93" name="Pins" color="2" fill="1" visible="no" active="yes"/>
<layer number="94" name="Symbols" color="4" fill="1" visible="yes" active="yes"/>
<layer number="95" name="Names" color="7" fill="1" visible="yes" active="yes"/>
<layer number="96" name="Values" color="7" fill="1" visible="yes" active="yes"/>
<layer number="97" name="Info" color="7" fill="1" visible="yes" active="yes"/>
<layer number="98" name="Guide" color="6" fill="1" visible="yes" active="yes"/>
<layer number="101" name="Hidden" color="15" fill="1" visible="yes" active="yes"/>
<layer number="102" name="Changes" color="12" fill="1" visible="yes" active="yes"/>
</layers>
<schematic xreflabel="%F%N/%S.%C%R" xrefpart="/%S.%C%R">
<libraries>
<library name="EK-TM4C123GXL">
<packages>
<package name="TM4C123LAUNCHPAD">
<description>&lt;B&gt;Two Dual In Line&lt;/B&gt;&lt;br&gt;
Samtec ESW-110-37-L-D&lt;br&gt;
or FCI 67997-210HLF, Digikey 609-3236-ND</description>
<wire x1="-19.05" y1="-11.303" x2="-19.05" y2="13.843" width="0.1524" layer="21"/>
<wire x1="-24.13" y1="13.843" x2="-19.05" y2="13.843" width="0.1524" layer="21"/>
<wire x1="-24.13" y1="-11.303" x2="-19.05" y2="-11.303" width="0.1524" layer="21"/>
<text x="-18.0578" y="17.4219" size="1.780340625" layer="25" ratio="10" rot="R180">&gt;NAME</text>
<text x="17.8045" y="15.5662" size="1.78045" layer="27" ratio="10">&gt;VALUE</text>
<wire x1="-24.13" y1="-11.303" x2="-24.13" y2="13.843" width="0.1524" layer="21"/>
<text x="-25.4232" y="13.9828" size="1.271159375" layer="21">1</text>
<text x="-25.4274" y="-12.7137" size="1.27136875" layer="21">10</text>
<text x="24.1476" y="-12.7092" size="1.27091875" layer="21">11</text>
<text x="24.1776" y="13.9976" size="1.272509375" layer="21">20</text>
<text x="-19.0623" y="13.979" size="1.27081875" layer="21">21</text>
<text x="-19.0721" y="-12.7148" size="1.27148125" layer="21">30</text>
<text x="17.7919" y="-12.7085" size="1.27085" layer="21">31</text>
<text x="17.7943" y="13.9813" size="1.27101875" layer="21">40</text>
<wire x1="19.05" y1="13.843" x2="24.13" y2="13.843" width="0.1524" layer="21"/>
<wire x1="19.05" y1="-11.303" x2="19.05" y2="13.843" width="0.1524" layer="21"/>
<wire x1="19.05" y1="-11.303" x2="24.13" y2="-11.303" width="0.1524" layer="21"/>
<wire x1="24.13" y1="-11.303" x2="24.13" y2="13.843" width="0.1524" layer="21"/>
<pad name="1" x="-22.86" y="12.7" drill="0.8" shape="square" rot="R90"/>
<pad name="2" x="-22.86" y="10.16" drill="0.8"/>
<pad name="3" x="-22.86" y="7.62" drill="0.8"/>
<pad name="4" x="-22.86" y="5.08" drill="0.8"/>
<pad name="5" x="-22.86" y="2.54" drill="0.8"/>
<pad name="6" x="-22.86" y="0" drill="0.8"/>
<pad name="7" x="-22.86" y="-2.54" drill="0.8"/>
<pad name="8" x="-22.86" y="-5.08" drill="0.8"/>
<pad name="9" x="-22.86" y="-7.62" drill="0.8"/>
<pad name="10" x="-22.86" y="-10.16" drill="0.8"/>
<pad name="11" x="22.86" y="-10.16" drill="0.8"/>
<pad name="12" x="22.86" y="-7.62" drill="0.8"/>
<pad name="13" x="22.86" y="-5.08" drill="0.8"/>
<pad name="14" x="22.86" y="-2.54" drill="0.8"/>
<pad name="15" x="22.86" y="0" drill="0.8"/>
<pad name="16" x="22.86" y="2.54" drill="0.8"/>
<pad name="17" x="22.86" y="5.08" drill="0.8"/>
<pad name="18" x="22.86" y="7.62" drill="0.8"/>
<pad name="19" x="22.86" y="10.16" drill="0.8"/>
<pad name="20" x="22.86" y="12.7" drill="0.8"/>
<pad name="21" x="-20.32" y="12.7" drill="0.8"/>
<pad name="22" x="-20.32" y="10.16" drill="0.8"/>
<pad name="23" x="-20.32" y="7.62" drill="0.8"/>
<pad name="24" x="-20.32" y="5.08" drill="0.8"/>
<pad name="25" x="-20.32" y="2.54" drill="0.8"/>
<pad name="26" x="-20.32" y="0" drill="0.8"/>
<pad name="27" x="-20.32" y="-2.54" drill="0.8"/>
<pad name="28" x="-20.32" y="-5.08" drill="0.8"/>
<pad name="29" x="-20.32" y="-7.62" drill="0.8"/>
<pad name="30" x="-20.32" y="-10.16" drill="0.8"/>
<pad name="31" x="20.32" y="-10.16" drill="0.8"/>
<pad name="32" x="20.32" y="-7.62" drill="0.8"/>
<pad name="33" x="20.32" y="-5.08" drill="0.8"/>
<pad name="34" x="20.32" y="-2.54" drill="0.8"/>
<pad name="35" x="20.32" y="0" drill="0.8"/>
<pad name="36" x="20.32" y="2.54" drill="0.8"/>
<pad name="37" x="20.32" y="5.08" drill="0.8"/>
<pad name="38" x="20.32" y="7.62" drill="0.8"/>
<pad name="39" x="20.32" y="10.16" drill="0.8"/>
<pad name="40" x="20.32" y="12.7" drill="0.8"/>
</package>
</packages>
<symbols>
<symbol name="TM4C123LAUNCHPAD">
<description>&lt;b&gt;TM4C123 LaunchPad&lt;/b&gt; has 40 pins</description>
<wire x1="-33.02" y1="15.24" x2="-33.02" y2="-15.24" width="0.2" layer="94"/>
<wire x1="-33.02" y1="-15.24" x2="-15.24" y2="-15.24" width="0.2" layer="94"/>
<text x="-30.5167" y="16.5299" size="1.780140625" layer="95">&gt;NAME</text>
<text x="-30.4929" y="-17.7875" size="1.77875" layer="96">&gt;VALUE</text>
<wire x1="-15.24" y1="15.24" x2="-33.02" y2="15.24" width="0.2" layer="94"/>
<wire x1="-15.24" y1="-15.24" x2="-15.24" y2="15.24" width="0.2" layer="94"/>
<text x="-30.4853" y="12.7022" size="1.778309375" layer="94">J1</text>
<text x="-20.3393" y="12.7121" size="1.779690625" layer="94">J3</text>
<text x="30.4844" y="12.7018" size="1.778259375" layer="94">J4</text>
<text x="40.6584" y="12.7057" size="1.7788" layer="94">J2</text>
<wire x1="27.94" y1="15.24" x2="27.94" y2="-15.24" width="0.2" layer="94"/>
<wire x1="45.72" y1="-15.24" x2="45.72" y2="15.24" width="0.2" layer="94"/>
<wire x1="45.72" y1="15.24" x2="27.94" y2="15.24" width="0.2" layer="94"/>
<wire x1="27.94" y1="-15.24" x2="45.72" y2="-15.24" width="0.2" layer="94"/>
<pin name="+3.3V" x="-35.56" y="10.16" length="short" direction="pwr"/>
<pin name="PB5" x="-35.56" y="7.62" length="short"/>
<pin name="PB0" x="-35.56" y="5.08" length="short"/>
<pin name="PB1" x="-35.56" y="2.54" length="short"/>
<pin name="PE4" x="-35.56" y="0" length="short"/>
<pin name="PA5" x="-35.56" y="-7.62" length="short"/>
<pin name="PA6" x="-35.56" y="-10.16" length="short"/>
<pin name="PA7" x="-35.56" y="-12.7" length="short"/>
<pin name="PA2" x="48.26" y="-12.7" length="short" rot="R180"/>
<pin name="PA3" x="48.26" y="-10.16" length="short" rot="R180"/>
<pin name="PA4" x="48.26" y="-7.62" length="short" rot="R180"/>
<pin name="PB6" x="48.26" y="-5.08" length="short" rot="R180"/>
<pin name="PB7" x="48.26" y="-2.54" length="short" rot="R180"/>
<pin name="RESET" x="48.26" y="0" length="short" direction="in" rot="R180"/>
<pin name="PF0" x="48.26" y="2.54" length="short" rot="R180"/>
<pin name="PE0" x="48.26" y="5.08" length="short" rot="R180"/>
<pin name="PB2" x="48.26" y="7.62" length="short" rot="R180"/>
<pin name="GND2" x="48.26" y="10.16" length="short" direction="pwr" rot="R180"/>
<pin name="+5V" x="-12.7" y="10.16" length="short" direction="pwr" rot="R180"/>
<pin name="GND" x="-12.7" y="7.62" length="short" direction="pwr" rot="R180"/>
<pin name="PD0" x="-12.7" y="5.08" length="short" rot="R180"/>
<pin name="PD1" x="-12.7" y="2.54" length="short" rot="R180"/>
<pin name="PE2" x="-12.7" y="-7.62" length="short" rot="R180"/>
<pin name="PE3" x="-12.7" y="-10.16" length="short" rot="R180"/>
<pin name="PF1" x="-12.7" y="-12.7" length="short" rot="R180"/>
<pin name="PF4" x="25.4" y="-12.7" length="short"/>
<pin name="PD7" x="25.4" y="-10.16" length="short"/>
<pin name="PD6" x="25.4" y="-7.62" length="short"/>
<pin name="PC7" x="25.4" y="-5.08" length="short"/>
<pin name="PC6" x="25.4" y="-2.54" length="short"/>
<pin name="PC5" x="25.4" y="0" length="short"/>
<pin name="PC4" x="25.4" y="2.54" length="short"/>
<pin name="PB3" x="25.4" y="5.08" length="short"/>
<pin name="PF3" x="25.4" y="7.62" length="short"/>
<pin name="PF2" x="25.4" y="10.16" length="short"/>
<pin name="PE5" x="-35.56" y="-2.54" length="short"/>
<pin name="PE1" x="-12.7" y="-5.08" length="short" rot="R180"/>
<pin name="PB4" x="-35.56" y="-5.08" length="short"/>
<pin name="PD3" x="-12.7" y="-2.54" length="short" rot="R180"/>
<pin name="PD2" x="-12.7" y="0" length="short" rot="R180"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="EK-TM4C123GXL" prefix="IC">
<description>&lt;b&gt;Texas Instruments TM4C123 LaunchPad&lt;/b&gt;&lt;p&gt;EK-TM4C123GXL
&lt;a href="http://www.ti.com/tool/ek-tm4c123gxl"&gt;www.ti.com/tool/ek-tm4c123gxl&lt;/a&gt;</description>
<gates>
<gate name="G$1" symbol="TM4C123LAUNCHPAD" x="0" y="0"/>
</gates>
<devices>
<device name="P" package="TM4C123LAUNCHPAD">
<connects>
<connect gate="G$1" pin="+3.3V" pad="1"/>
<connect gate="G$1" pin="+5V" pad="21"/>
<connect gate="G$1" pin="GND" pad="22"/>
<connect gate="G$1" pin="GND2" pad="20"/>
<connect gate="G$1" pin="PA2" pad="11"/>
<connect gate="G$1" pin="PA3" pad="12"/>
<connect gate="G$1" pin="PA4" pad="13"/>
<connect gate="G$1" pin="PA5" pad="8"/>
<connect gate="G$1" pin="PA6" pad="9"/>
<connect gate="G$1" pin="PA7" pad="10"/>
<connect gate="G$1" pin="PB0" pad="3"/>
<connect gate="G$1" pin="PB1" pad="4"/>
<connect gate="G$1" pin="PB2" pad="19"/>
<connect gate="G$1" pin="PB3" pad="38"/>
<connect gate="G$1" pin="PB4" pad="7"/>
<connect gate="G$1" pin="PB5" pad="2"/>
<connect gate="G$1" pin="PB6" pad="14"/>
<connect gate="G$1" pin="PB7" pad="15"/>
<connect gate="G$1" pin="PC4" pad="37"/>
<connect gate="G$1" pin="PC5" pad="36"/>
<connect gate="G$1" pin="PC6" pad="35"/>
<connect gate="G$1" pin="PC7" pad="34"/>
<connect gate="G$1" pin="PD0" pad="23"/>
<connect gate="G$1" pin="PD1" pad="24"/>
<connect gate="G$1" pin="PD2" pad="25"/>
<connect gate="G$1" pin="PD3" pad="26"/>
<connect gate="G$1" pin="PD6" pad="33"/>
<connect gate="G$1" pin="PD7" pad="32"/>
<connect gate="G$1" pin="PE0" pad="18"/>
<connect gate="G$1" pin="PE1" pad="27"/>
<connect gate="G$1" pin="PE2" pad="28"/>
<connect gate="G$1" pin="PE3" pad="29"/>
<connect gate="G$1" pin="PE4" pad="5"/>
<connect gate="G$1" pin="PE5" pad="6"/>
<connect gate="G$1" pin="PF0" pad="17"/>
<connect gate="G$1" pin="PF1" pad="30"/>
<connect gate="G$1" pin="PF2" pad="40"/>
<connect gate="G$1" pin="PF3" pad="39"/>
<connect gate="G$1" pin="PF4" pad="31"/>
<connect gate="G$1" pin="RESET" pad="16"/>
</connects>
<technologies>
<technology name="">
<attribute name="AVAILABILITY" value="Unavailable"/>
<attribute name="DESCRIPTION" value=" TM4C123G LaunchPad™ Tiva™ C ARM® Cortex®-M4F MCU 32-Bit Embedded Evaluation Board "/>
<attribute name="MF" value="Texas Instruments"/>
<attribute name="MP" value="EK-TM4C123GXL"/>
<attribute name="PACKAGE" value="None"/>
<attribute name="PRICE" value="None"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="frames" urn="urn:adsk.eagle:library:229">
<description>&lt;b&gt;Frames for Sheet and Layout&lt;/b&gt;</description>
<packages>
</packages>
<symbols>
<symbol name="A3L-LOC" urn="urn:adsk.eagle:symbol:13881/1" library_version="1">
<wire x1="288.29" y1="3.81" x2="342.265" y2="3.81" width="0.1016" layer="94"/>
<wire x1="342.265" y1="3.81" x2="373.38" y2="3.81" width="0.1016" layer="94"/>
<wire x1="373.38" y1="3.81" x2="383.54" y2="3.81" width="0.1016" layer="94"/>
<wire x1="383.54" y1="3.81" x2="383.54" y2="8.89" width="0.1016" layer="94"/>
<wire x1="383.54" y1="8.89" x2="383.54" y2="13.97" width="0.1016" layer="94"/>
<wire x1="383.54" y1="13.97" x2="383.54" y2="19.05" width="0.1016" layer="94"/>
<wire x1="383.54" y1="19.05" x2="383.54" y2="24.13" width="0.1016" layer="94"/>
<wire x1="288.29" y1="3.81" x2="288.29" y2="24.13" width="0.1016" layer="94"/>
<wire x1="288.29" y1="24.13" x2="342.265" y2="24.13" width="0.1016" layer="94"/>
<wire x1="342.265" y1="24.13" x2="383.54" y2="24.13" width="0.1016" layer="94"/>
<wire x1="373.38" y1="3.81" x2="373.38" y2="8.89" width="0.1016" layer="94"/>
<wire x1="373.38" y1="8.89" x2="383.54" y2="8.89" width="0.1016" layer="94"/>
<wire x1="373.38" y1="8.89" x2="342.265" y2="8.89" width="0.1016" layer="94"/>
<wire x1="342.265" y1="8.89" x2="342.265" y2="3.81" width="0.1016" layer="94"/>
<wire x1="342.265" y1="8.89" x2="342.265" y2="13.97" width="0.1016" layer="94"/>
<wire x1="342.265" y1="13.97" x2="383.54" y2="13.97" width="0.1016" layer="94"/>
<wire x1="342.265" y1="13.97" x2="342.265" y2="19.05" width="0.1016" layer="94"/>
<wire x1="342.265" y1="19.05" x2="383.54" y2="19.05" width="0.1016" layer="94"/>
<wire x1="342.265" y1="19.05" x2="342.265" y2="24.13" width="0.1016" layer="94"/>
<text x="344.17" y="15.24" size="2.54" layer="94">&gt;DRAWING_NAME</text>
<text x="344.17" y="10.16" size="2.286" layer="94">&gt;LAST_DATE_TIME</text>
<text x="357.505" y="5.08" size="2.54" layer="94">&gt;SHEET</text>
<text x="343.916" y="4.953" size="2.54" layer="94">Sheet:</text>
<frame x1="0" y1="0" x2="387.35" y2="260.35" columns="8" rows="5" layer="94"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="A3L-LOC" urn="urn:adsk.eagle:component:13942/1" prefix="FRAME" uservalue="yes" library_version="1">
<description>&lt;b&gt;FRAME&lt;/b&gt;&lt;p&gt;
DIN A3, landscape with location and doc. field</description>
<gates>
<gate name="G$1" symbol="A3L-LOC" x="0" y="0"/>
</gates>
<devices>
<device name="">
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="SIM800L">
<packages>
<package name="SIP">
<wire x1="0" y1="0" x2="0" y2="27" width="0.127" layer="39"/>
<wire x1="0" y1="0" x2="40" y2="0" width="0.127" layer="39"/>
<wire x1="0" y1="27" x2="40" y2="27" width="0.127" layer="39"/>
<wire x1="40" y1="0" x2="40" y2="27" width="0.127" layer="39"/>
<hole x="2.87" y="24.13" drill="3.2"/>
<hole x="2.87" y="2.87" drill="3.2"/>
<pad name="1" x="38.1" y="19.24" drill="1.2" shape="octagon"/>
<pad name="2" x="38.1" y="16.7" drill="1.2" shape="octagon"/>
<pad name="3" x="38.1" y="14.16" drill="1.2" shape="octagon"/>
<pad name="4" x="38.1" y="11.62" drill="1.2" shape="octagon"/>
<pad name="5" x="38.1" y="9.08" drill="1.2" shape="octagon"/>
<pad name="6" x="38.1" y="6.54" drill="1.2" shape="octagon"/>
<pad name="7" x="38.1" y="4" drill="1.2" shape="octagon"/>
<hole x="37.16" y="24.13" drill="3.2"/>
</package>
</packages>
<symbols>
<symbol name="SIM800L">
<pin name="RST" x="7.62" y="5.08" length="middle" rot="R180"/>
<pin name="TXD" x="-15.24" y="0" length="middle"/>
<pin name="VDD" x="-15.24" y="5.08" length="middle"/>
<pin name="5V" x="-15.24" y="10.16" length="middle"/>
<pin name="RXD" x="7.62" y="0" length="middle" rot="R180"/>
<pin name="GND" x="7.62" y="10.16" length="middle" rot="R180"/>
<wire x1="-10.16" y1="12.7" x2="-10.16" y2="-2.54" width="0.254" layer="94"/>
<wire x1="-10.16" y1="-2.54" x2="2.54" y2="-2.54" width="0.254" layer="94"/>
<wire x1="2.54" y1="-2.54" x2="2.54" y2="12.7" width="0.254" layer="94"/>
<wire x1="2.54" y1="12.7" x2="-10.16" y2="12.7" width="0.254" layer="94"/>
<text x="0" y="15.24" size="1.778" layer="94" rot="R180">SIM800L</text>
</symbol>
</symbols>
<devicesets>
<deviceset name="SIM800L">
<description>SIM800L Blue EVB Board with Level Translation and diode dropper.</description>
<gates>
<gate name="G$1" symbol="SIM800L" x="22.86" y="5.08"/>
</gates>
<devices>
<device name="" package="SIP">
<connects>
<connect gate="G$1" pin="5V" pad="1"/>
<connect gate="G$1" pin="GND" pad="2 6"/>
<connect gate="G$1" pin="RST" pad="7"/>
<connect gate="G$1" pin="RXD" pad="5"/>
<connect gate="G$1" pin="TXD" pad="4"/>
<connect gate="G$1" pin="VDD" pad="3"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="diy-modules">
<description>&lt;b&gt;DIY Modules for Arduino, Raspberry Pi, CubieBoard etc.&lt;/b&gt;
&lt;br&gt;&lt;br&gt;
The library contains a list of symbols and footprints for popular, cheap and easy-to-use electronic modules.&lt;br&gt;
The modules are intend to work with microprocessor-based platforms such as &lt;a href="http://arduino.cc"&gt;Arduino&lt;/a&gt;, &lt;a href="http://raspberrypi.org/"&gt;Raspberry Pi&lt;/a&gt;, &lt;a href="http://cubieboard.org/"&gt;CubieBoard&lt;/a&gt;, &lt;a href="http://beagleboard.org/"&gt;BeagleBone&lt;/a&gt; and many others. There are many manufacturers of the modules in the world. Almost all of them can be bought on &lt;a href="ebay.com"&gt;ebay.com&lt;/a&gt;.&lt;br&gt;
&lt;br&gt;
By using this library, you can design a PCB for devices created with usage of modules. Even if you do not need to create PCB design, you can also use the library to quickly document your work by drawing schematics of devices built by you.&lt;br&gt;
&lt;br&gt;
The latest version, examples, photos and much more can be found at: &lt;b&gt;&lt;a href="http://diymodules.org/eagle"&gt;diymodules.org/eagle&lt;/a&gt;&lt;/b&gt;&lt;br&gt;&lt;br&gt;
Comments, suggestions and bug reports please send to: &lt;b&gt;&lt;a href="mailto:eagle@diymodules.org"&gt;eagle@diymodules.org&lt;/b&gt;&lt;/a&gt;&lt;br&gt;&lt;br&gt;
&lt;i&gt;Version: 1.8.0 (2017-Jul-02)&lt;/i&gt;&lt;br&gt;
&lt;i&gt;Created by: Miroslaw Brudnowski&lt;/i&gt;&lt;br&gt;&lt;br&gt;
&lt;i&gt;Released under the Creative Commons Attribution 4.0 International License: &lt;a href="http://creativecommons.org/licenses/by/4.0"&gt;http://creativecommons.org/licenses/by/4.0&lt;/a&gt;&lt;/i&gt;
&lt;br&gt;&lt;br&gt;
&lt;center&gt;
&lt;a href="http://diymodules.org/eagle"&gt;&lt;img src="http://www.diymodules.org/img/diymodules-lbr-image.php?v=1.8.0" alt="DIYmodules.org"&gt;&lt;/a&gt;
&lt;/center&gt;</description>
<packages>
<package name="WIRELESS-WIFI-ESP-01">
<description>&lt;b&gt;Wireless Wi-Fi ESP-01 Module&lt;/b&gt; based on &lt;b&gt;ESP8266&lt;/b&gt; chip</description>
<wire x1="-12.7" y1="7.366" x2="6.35" y2="7.366" width="0.127" layer="21"/>
<wire x1="6.35" y1="7.366" x2="12.7" y2="7.366" width="0.127" layer="21"/>
<wire x1="12.7" y1="7.366" x2="12.7" y2="-7.366" width="0.127" layer="21"/>
<wire x1="12.7" y1="-7.366" x2="6.35" y2="-7.366" width="0.127" layer="21"/>
<wire x1="6.35" y1="-7.366" x2="-12.7" y2="-7.366" width="0.127" layer="21"/>
<wire x1="-12.7" y1="-7.366" x2="-12.7" y2="-4.445" width="0.127" layer="21"/>
<pad name="A1" x="-8.89" y="3.81" drill="1" shape="square"/>
<pad name="B1" x="-8.89" y="1.27" drill="1"/>
<pad name="C1" x="-8.89" y="-1.27" drill="1"/>
<pad name="C2" x="-11.43" y="-1.27" drill="1"/>
<pad name="B2" x="-11.43" y="1.27" drill="1"/>
<pad name="A2" x="-11.43" y="3.81" drill="1"/>
<pad name="D2" x="-11.43" y="-3.81" drill="1"/>
<pad name="D1" x="-8.89" y="-3.81" drill="1" shape="square"/>
<wire x1="-12.7" y1="-4.445" x2="-12.7" y2="-3.175" width="0.127" layer="21"/>
<wire x1="-12.7" y1="-3.175" x2="-12.7" y2="-1.905" width="0.127" layer="21"/>
<wire x1="-12.7" y1="-1.905" x2="-12.7" y2="-0.635" width="0.127" layer="21"/>
<wire x1="-12.7" y1="-0.635" x2="-12.7" y2="0.635" width="0.127" layer="21"/>
<wire x1="-12.7" y1="0.635" x2="-12.7" y2="1.905" width="0.127" layer="21"/>
<wire x1="-12.7" y1="1.905" x2="-12.7" y2="3.175" width="0.127" layer="21"/>
<wire x1="-12.7" y1="3.175" x2="-12.7" y2="4.445" width="0.127" layer="21"/>
<wire x1="-12.7" y1="4.445" x2="-12.7" y2="7.366" width="0.127" layer="21"/>
<wire x1="6.35" y1="7.366" x2="6.35" y2="-7.366" width="0.127" layer="21"/>
<text x="9.525" y="0" size="1.778" layer="21" rot="R90" align="center">ANTENNA</text>
<wire x1="-12.7" y1="4.445" x2="-12.065" y2="5.08" width="0.127" layer="21"/>
<wire x1="-12.065" y1="5.08" x2="-10.795" y2="5.08" width="0.127" layer="21"/>
<wire x1="-10.795" y1="5.08" x2="-10.16" y2="4.445" width="0.127" layer="21"/>
<wire x1="-10.16" y1="4.445" x2="-9.525" y2="5.08" width="0.127" layer="21"/>
<wire x1="-9.525" y1="5.08" x2="-8.255" y2="5.08" width="0.127" layer="21"/>
<wire x1="-8.255" y1="5.08" x2="-7.62" y2="4.445" width="0.127" layer="21"/>
<wire x1="-7.62" y1="4.445" x2="-7.62" y2="3.175" width="0.127" layer="21"/>
<wire x1="-7.62" y1="3.175" x2="-8.255" y2="2.54" width="0.127" layer="21"/>
<wire x1="-8.255" y1="2.54" x2="-7.62" y2="1.905" width="0.127" layer="21"/>
<wire x1="-7.62" y1="1.905" x2="-7.62" y2="0.635" width="0.127" layer="21"/>
<wire x1="-7.62" y1="0.635" x2="-8.255" y2="0" width="0.127" layer="21"/>
<wire x1="-8.255" y1="0" x2="-7.62" y2="-0.635" width="0.127" layer="21"/>
<wire x1="-7.62" y1="-0.635" x2="-7.62" y2="-1.905" width="0.127" layer="21"/>
<wire x1="-7.62" y1="-1.905" x2="-8.255" y2="-2.54" width="0.127" layer="21"/>
<wire x1="-8.255" y1="-2.54" x2="-7.62" y2="-3.175" width="0.127" layer="21"/>
<wire x1="-7.62" y1="-3.175" x2="-7.62" y2="-4.445" width="0.127" layer="21"/>
<wire x1="-7.62" y1="-4.445" x2="-8.255" y2="-5.08" width="0.127" layer="21"/>
<wire x1="-8.255" y1="-5.08" x2="-9.525" y2="-5.08" width="0.127" layer="21"/>
<wire x1="-9.525" y1="-5.08" x2="-10.16" y2="-4.445" width="0.127" layer="21"/>
<wire x1="-10.16" y1="-4.445" x2="-10.795" y2="-5.08" width="0.127" layer="21"/>
<wire x1="-10.795" y1="-5.08" x2="-12.065" y2="-5.08" width="0.127" layer="21"/>
<wire x1="-12.065" y1="-5.08" x2="-12.7" y2="-4.445" width="0.127" layer="21"/>
<wire x1="-12.7" y1="-3.175" x2="-12.065" y2="-2.54" width="0.127" layer="21"/>
<wire x1="-12.065" y1="-2.54" x2="-12.7" y2="-1.905" width="0.127" layer="21"/>
<wire x1="-12.7" y1="-0.635" x2="-12.065" y2="0" width="0.127" layer="21"/>
<wire x1="-12.065" y1="0" x2="-12.7" y2="0.635" width="0.127" layer="21"/>
<wire x1="-12.7" y1="1.905" x2="-12.065" y2="2.54" width="0.127" layer="21"/>
<wire x1="-12.065" y1="2.54" x2="-12.7" y2="3.175" width="0.127" layer="21"/>
<text x="0" y="8.255" size="1.27" layer="25" align="bottom-center">&gt;NAME</text>
<text x="0" y="-8.255" size="1.27" layer="27" align="top-center">&gt;VALUE</text>
</package>
<package name="ULTRASONIC-HC-SR04">
<description>&lt;b&gt;Ultrasonic Ranging Module HC-SR04&lt;/b&gt;</description>
<wire x1="-22.5" y1="9.8" x2="22.5" y2="9.8" width="0.127" layer="21"/>
<wire x1="22.5" y1="9.8" x2="22.5" y2="-10.2" width="0.127" layer="21"/>
<wire x1="22.5" y1="-10.2" x2="-22.5" y2="-10.2" width="0.127" layer="21"/>
<wire x1="-22.5" y1="-10.2" x2="-22.5" y2="9.8" width="0.127" layer="21"/>
<hole x="-21.1" y="8.4" drill="1.8"/>
<hole x="-21.1" y="-8.8" drill="1.8"/>
<hole x="21.1" y="-8.8" drill="1.8"/>
<hole x="21.1" y="8.4" drill="1.8"/>
<circle x="-13" y="0" radius="8" width="0.127" layer="21"/>
<circle x="13" y="0" radius="8" width="0.127" layer="21"/>
<pad name="1" x="-3.81" y="-8.89" drill="1" shape="square"/>
<pad name="2" x="-1.27" y="-8.89" drill="1"/>
<pad name="3" x="1.27" y="-8.89" drill="1"/>
<pad name="4" x="3.81" y="-8.89" drill="1"/>
<wire x1="-5.08" y1="-8.255" x2="-4.445" y2="-7.62" width="0.127" layer="21"/>
<wire x1="-4.445" y1="-7.62" x2="-3.175" y2="-7.62" width="0.127" layer="21"/>
<wire x1="-3.175" y1="-7.62" x2="-2.54" y2="-8.255" width="0.127" layer="21"/>
<wire x1="-2.54" y1="-8.255" x2="-1.905" y2="-7.62" width="0.127" layer="21"/>
<wire x1="-1.905" y1="-7.62" x2="-0.635" y2="-7.62" width="0.127" layer="21"/>
<wire x1="-0.635" y1="-7.62" x2="0" y2="-8.255" width="0.127" layer="21"/>
<wire x1="0" y1="-8.255" x2="0.635" y2="-7.62" width="0.127" layer="21"/>
<wire x1="0.635" y1="-7.62" x2="1.905" y2="-7.62" width="0.127" layer="21"/>
<wire x1="1.905" y1="-7.62" x2="2.54" y2="-8.255" width="0.127" layer="21"/>
<wire x1="2.54" y1="-8.255" x2="3.175" y2="-7.62" width="0.127" layer="21"/>
<wire x1="3.175" y1="-7.62" x2="4.445" y2="-7.62" width="0.127" layer="21"/>
<wire x1="4.445" y1="-7.62" x2="5.08" y2="-8.255" width="0.127" layer="21"/>
<wire x1="5.08" y1="-8.255" x2="5.08" y2="-9.525" width="0.127" layer="21"/>
<wire x1="5.08" y1="-9.525" x2="4.445" y2="-10.16" width="0.127" layer="21"/>
<wire x1="4.445" y1="-10.16" x2="3.175" y2="-10.16" width="0.127" layer="21"/>
<wire x1="3.175" y1="-10.16" x2="2.54" y2="-9.525" width="0.127" layer="21"/>
<wire x1="2.54" y1="-9.525" x2="1.905" y2="-10.16" width="0.127" layer="21"/>
<wire x1="1.905" y1="-10.16" x2="0.635" y2="-10.16" width="0.127" layer="21"/>
<wire x1="0.635" y1="-10.16" x2="0" y2="-9.525" width="0.127" layer="21"/>
<wire x1="0" y1="-9.525" x2="-0.635" y2="-10.16" width="0.127" layer="21"/>
<wire x1="-0.635" y1="-10.16" x2="-1.905" y2="-10.16" width="0.127" layer="21"/>
<wire x1="-1.905" y1="-10.16" x2="-2.54" y2="-9.525" width="0.127" layer="21"/>
<wire x1="-2.54" y1="-9.525" x2="-3.175" y2="-10.16" width="0.127" layer="21"/>
<wire x1="-3.175" y1="-10.16" x2="-4.445" y2="-10.16" width="0.127" layer="21"/>
<wire x1="-4.445" y1="-10.16" x2="-5.08" y2="-9.525" width="0.127" layer="21"/>
<wire x1="-5.08" y1="-9.525" x2="-5.08" y2="-8.255" width="0.127" layer="21"/>
<text x="0" y="10.795" size="1.27" layer="25" align="bottom-center">&gt;NAME</text>
<text x="0" y="-11.43" size="1.27" layer="27" align="top-center">&gt;VALUE</text>
</package>
<package name="ULTRASONIC-HC-SR04#V">
<description>&lt;b&gt;Ultrasonic Ranging Module HC-SR04&lt;/b&gt; vertically mounted</description>
<wire x1="-22.5" y1="-4.064" x2="22.5" y2="-4.064" width="0.127" layer="21"/>
<wire x1="22.5" y1="-4.064" x2="22.5" y2="-5.7" width="0.127" layer="21"/>
<wire x1="22.5" y1="-5.7" x2="21" y2="-5.7" width="0.127" layer="21"/>
<wire x1="21" y1="-5.7" x2="5" y2="-5.7" width="0.127" layer="21"/>
<wire x1="5" y1="-5.7" x2="-5" y2="-5.7" width="0.127" layer="21"/>
<wire x1="-5" y1="-5.7" x2="-21" y2="-5.7" width="0.127" layer="21"/>
<wire x1="-21" y1="-5.7" x2="-22.5" y2="-5.7" width="0.127" layer="21"/>
<wire x1="-22.5" y1="-5.7" x2="-22.5" y2="-4.064" width="0.127" layer="21"/>
<wire x1="-5.08" y1="-4.064" x2="5.08" y2="-4.064" width="0.127" layer="21"/>
<pad name="1" x="-3.81" y="0" drill="1" shape="square" rot="R180"/>
<pad name="2" x="-1.27" y="0" drill="1" rot="R180"/>
<pad name="3" x="1.27" y="0" drill="1" rot="R180"/>
<pad name="4" x="3.81" y="0" drill="1" rot="R180"/>
<text x="0" y="1.905" size="1.27" layer="25" align="bottom-center">&gt;NAME</text>
<text x="0" y="-18.415" size="1.27" layer="27" align="top-center">&gt;VALUE</text>
<wire x1="-5.08" y1="-4.064" x2="-5.08" y2="-1.524" width="0.127" layer="21"/>
<wire x1="-5.08" y1="-1.524" x2="-4.191" y2="-1.524" width="0.127" layer="21"/>
<wire x1="-4.191" y1="-1.524" x2="-3.429" y2="-1.524" width="0.127" layer="21"/>
<wire x1="-3.429" y1="-1.524" x2="-1.651" y2="-1.524" width="0.127" layer="21"/>
<wire x1="-1.651" y1="-1.524" x2="-0.889" y2="-1.524" width="0.127" layer="21"/>
<wire x1="-0.889" y1="-1.524" x2="0.889" y2="-1.524" width="0.127" layer="21"/>
<wire x1="0.889" y1="-1.524" x2="1.651" y2="-1.524" width="0.127" layer="21"/>
<wire x1="1.651" y1="-1.524" x2="3.429" y2="-1.524" width="0.127" layer="21"/>
<wire x1="3.429" y1="-1.524" x2="4.191" y2="-1.524" width="0.127" layer="21"/>
<wire x1="4.191" y1="-1.524" x2="5.08" y2="-1.524" width="0.127" layer="21"/>
<wire x1="5.08" y1="-1.524" x2="5.08" y2="-4.064" width="0.127" layer="21"/>
<wire x1="4.191" y1="-1.524" x2="4.191" y2="-0.889" width="0.127" layer="21"/>
<wire x1="3.429" y1="-1.524" x2="3.429" y2="-0.889" width="0.127" layer="21"/>
<wire x1="1.651" y1="-1.524" x2="1.651" y2="-0.889" width="0.127" layer="21"/>
<wire x1="-0.889" y1="-1.524" x2="-0.889" y2="-0.889" width="0.127" layer="21"/>
<wire x1="-3.429" y1="-1.524" x2="-3.429" y2="-0.889" width="0.127" layer="21"/>
<wire x1="0.889" y1="-1.524" x2="0.889" y2="-0.889" width="0.127" layer="21"/>
<wire x1="-1.651" y1="-1.524" x2="-1.651" y2="-0.889" width="0.127" layer="21"/>
<wire x1="-4.191" y1="-1.524" x2="-4.191" y2="-0.889" width="0.127" layer="21"/>
<wire x1="-21" y1="-5.7" x2="-21" y2="-17.7" width="0.127" layer="21"/>
<wire x1="-21" y1="-17.7" x2="-5" y2="-17.7" width="0.127" layer="21"/>
<wire x1="-5" y1="-17.7" x2="-5" y2="-5.7" width="0.127" layer="21"/>
<wire x1="5" y1="-5.7" x2="5" y2="-17.7" width="0.127" layer="21"/>
<wire x1="5" y1="-17.7" x2="21" y2="-17.7" width="0.127" layer="21"/>
<wire x1="21" y1="-17.7" x2="21" y2="-5.7" width="0.127" layer="21"/>
</package>
<package name="WIRELESS-BLUETOOTH-HC-05">
<description>&lt;b&gt;Bluetooth Transceiver Module&lt;/b&gt; based on &lt;b&gt;HC-05&lt;/b&gt; board</description>
<pad name="2" x="-3.81" y="-17.145" drill="1"/>
<pad name="1" x="-6.35" y="-17.145" drill="1" shape="square"/>
<pad name="3" x="-1.27" y="-17.145" drill="1"/>
<wire x1="-8.255" y1="-18.415" x2="-6.985" y2="-18.415" width="0.127" layer="21"/>
<wire x1="-6.985" y1="-18.415" x2="-5.715" y2="-18.415" width="0.127" layer="21"/>
<wire x1="-5.715" y1="-18.415" x2="-4.445" y2="-18.415" width="0.127" layer="21"/>
<wire x1="-4.445" y1="-18.415" x2="-3.175" y2="-18.415" width="0.127" layer="21"/>
<wire x1="-3.175" y1="-18.415" x2="-1.905" y2="-18.415" width="0.127" layer="21"/>
<wire x1="-1.905" y1="-18.415" x2="-0.635" y2="-18.415" width="0.127" layer="21"/>
<wire x1="-0.635" y1="-18.415" x2="8.255" y2="-18.415" width="0.127" layer="21"/>
<wire x1="8.255" y1="-18.415" x2="8.255" y2="18.415" width="0.127" layer="21"/>
<wire x1="8.255" y1="18.415" x2="6.604" y2="18.415" width="0.127" layer="21"/>
<wire x1="6.604" y1="18.415" x2="-6.604" y2="18.415" width="0.127" layer="21"/>
<wire x1="-6.604" y1="18.415" x2="-8.255" y2="18.415" width="0.127" layer="21"/>
<wire x1="-8.255" y1="18.415" x2="-8.255" y2="-18.415" width="0.127" layer="21"/>
<wire x1="0" y1="-16.51" x2="0.635" y2="-15.875" width="0.127" layer="21"/>
<wire x1="0.635" y1="-15.875" x2="1.905" y2="-15.875" width="0.127" layer="21"/>
<wire x1="1.905" y1="-15.875" x2="2.54" y2="-16.51" width="0.127" layer="21"/>
<wire x1="2.54" y1="-16.51" x2="3.175" y2="-15.875" width="0.127" layer="21"/>
<wire x1="3.175" y1="-15.875" x2="4.445" y2="-15.875" width="0.127" layer="21"/>
<wire x1="4.445" y1="-15.875" x2="5.08" y2="-16.51" width="0.127" layer="21"/>
<wire x1="5.08" y1="-16.51" x2="5.715" y2="-15.875" width="0.127" layer="21"/>
<wire x1="5.715" y1="-15.875" x2="6.985" y2="-15.875" width="0.127" layer="21"/>
<wire x1="7.62" y1="-17.78" x2="6.985" y2="-18.415" width="0.127" layer="21"/>
<wire x1="5.715" y1="-18.415" x2="5.08" y2="-17.78" width="0.127" layer="21"/>
<wire x1="5.08" y1="-17.78" x2="4.445" y2="-18.415" width="0.127" layer="21"/>
<wire x1="3.175" y1="-18.415" x2="2.54" y2="-17.78" width="0.127" layer="21"/>
<wire x1="2.54" y1="-17.78" x2="1.905" y2="-18.415" width="0.127" layer="21"/>
<wire x1="0.635" y1="-18.415" x2="0" y2="-17.78" width="0.127" layer="21"/>
<text x="0" y="19.685" size="1.27" layer="25" align="bottom-center">&gt;NAME</text>
<text x="0" y="-19.685" size="1.27" layer="27" align="top-center">&gt;VALUE</text>
<wire x1="7.62" y1="-17.78" x2="7.62" y2="-16.51" width="0.127" layer="21"/>
<wire x1="7.62" y1="-16.51" x2="6.985" y2="-15.875" width="0.127" layer="21"/>
<pad name="4" x="1.27" y="-17.145" drill="1"/>
<pad name="5" x="3.81" y="-17.145" drill="1"/>
<pad name="6" x="6.35" y="-17.145" drill="1"/>
<wire x1="0" y1="-16.51" x2="-0.635" y2="-15.875" width="0.127" layer="21"/>
<wire x1="-0.635" y1="-15.875" x2="-1.905" y2="-15.875" width="0.127" layer="21"/>
<wire x1="-1.905" y1="-15.875" x2="-2.54" y2="-16.51" width="0.127" layer="21"/>
<wire x1="-2.54" y1="-16.51" x2="-3.175" y2="-15.875" width="0.127" layer="21"/>
<wire x1="-3.175" y1="-15.875" x2="-4.445" y2="-15.875" width="0.127" layer="21"/>
<wire x1="-4.445" y1="-15.875" x2="-5.08" y2="-16.51" width="0.127" layer="21"/>
<wire x1="-5.08" y1="-16.51" x2="-5.715" y2="-15.875" width="0.127" layer="21"/>
<wire x1="-5.715" y1="-15.875" x2="-6.985" y2="-15.875" width="0.127" layer="21"/>
<wire x1="-6.985" y1="-15.875" x2="-7.62" y2="-16.51" width="0.127" layer="21"/>
<wire x1="-7.62" y1="-16.51" x2="-7.62" y2="-17.78" width="0.127" layer="21"/>
<wire x1="-7.62" y1="-17.78" x2="-6.985" y2="-18.415" width="0.127" layer="21"/>
<wire x1="-5.715" y1="-18.415" x2="-5.08" y2="-17.78" width="0.127" layer="21"/>
<wire x1="-5.08" y1="-17.78" x2="-4.445" y2="-18.415" width="0.127" layer="21"/>
<wire x1="-3.175" y1="-18.415" x2="-2.54" y2="-17.78" width="0.127" layer="21"/>
<wire x1="-2.54" y1="-17.78" x2="-1.905" y2="-18.415" width="0.127" layer="21"/>
<wire x1="-0.635" y1="-18.415" x2="0" y2="-17.78" width="0.127" layer="21"/>
<wire x1="-6.604" y1="18.415" x2="-6.604" y2="14.605" width="0.127" layer="21"/>
<wire x1="-6.604" y1="14.605" x2="-6.604" y2="-8.255" width="0.127" layer="21"/>
<wire x1="-6.604" y1="-8.255" x2="6.604" y2="-8.255" width="0.127" layer="21"/>
<wire x1="6.604" y1="-8.255" x2="6.604" y2="14.605" width="0.127" layer="21"/>
<text x="-6.35" y="-15.24" size="1.27" layer="21" rot="R90" align="center-left">STATE</text>
<text x="-3.81" y="-15.24" size="1.27" layer="21" rot="R90" align="center-left">RX</text>
<text x="-1.27" y="-15.24" size="1.27" layer="21" rot="R90" align="center-left">TX</text>
<text x="1.27" y="-15.24" size="1.27" layer="21" rot="R90" align="center-left">GND</text>
<text x="3.81" y="-15.24" size="1.27" layer="21" rot="R90" align="center-left">+5V</text>
<text x="6.35" y="-15.24" size="1.27" layer="21" rot="R90" align="center-left">EN</text>
<wire x1="6.604" y1="14.605" x2="6.604" y2="18.415" width="0.127" layer="21"/>
<wire x1="-6.604" y1="14.605" x2="6.604" y2="14.605" width="0.127" layer="21"/>
<text x="0" y="16.51" size="1.524" layer="21" align="center">ANTENNA</text>
</package>
<package name="DC-DC-STEP-DOWN-LM2596">
<description>&lt;b&gt;DC/DC Step-Down Regulator&lt;/b&gt; based on &lt;b&gt;LM2596-ADJ&lt;/b&gt; chip</description>
<wire x1="-21.59" y1="10.414" x2="21.59" y2="10.414" width="0.127" layer="21"/>
<wire x1="21.59" y1="10.414" x2="21.59" y2="-10.414" width="0.127" layer="21"/>
<wire x1="21.59" y1="-10.414" x2="-21.59" y2="-10.414" width="0.127" layer="21"/>
<wire x1="-21.59" y1="-10.414" x2="-21.59" y2="10.414" width="0.127" layer="21"/>
<pad name="IN+" x="-19.812" y="8.636" drill="1.5" diameter="2.5" shape="square"/>
<pad name="IN-" x="-19.812" y="-8.636" drill="1.5" diameter="2.5" shape="square"/>
<pad name="OUT-" x="19.812" y="-8.636" drill="1.5" diameter="2.5" shape="square"/>
<pad name="OUT+" x="19.812" y="8.636" drill="1.5" diameter="2.5" shape="square"/>
<hole x="-14.478" y="7.62" drill="3"/>
<hole x="15.24" y="-7.62" drill="3"/>
<text x="0" y="11.43" size="1.27" layer="25" align="bottom-center">&gt;NAME</text>
<text x="0" y="-11.43" size="1.27" layer="27" align="top-center">&gt;VALUE</text>
<text x="-19.685" y="0" size="1.778" layer="21" rot="R90" align="center">IN</text>
<text x="19.685" y="0" size="1.778" layer="21" rot="R90" align="center">OUT</text>
<wire x1="19.685" y1="6.985" x2="19.685" y2="5.715" width="0.254" layer="21"/>
<wire x1="19.05" y1="6.35" x2="20.32" y2="6.35" width="0.254" layer="21"/>
<wire x1="-19.685" y1="-6.985" x2="-19.685" y2="-5.715" width="0.254" layer="21"/>
<wire x1="19.685" y1="-6.985" x2="19.685" y2="-5.715" width="0.254" layer="21"/>
<wire x1="-19.685" y1="6.985" x2="-19.685" y2="5.715" width="0.254" layer="21"/>
<wire x1="-20.32" y1="6.35" x2="-19.05" y2="6.35" width="0.254" layer="21"/>
</package>
</packages>
<symbols>
<symbol name="WIRELESS-WIFI-ESP-01">
<description>&lt;b&gt;Wireless Wi-Fi ESP-01 Module&lt;/b&gt; based on &lt;b&gt;ESP8266&lt;/b&gt; chip</description>
<pin name="GND" x="-22.86" y="10.16" length="middle" direction="pwr"/>
<pin name="UTXD" x="-22.86" y="7.62" length="middle"/>
<pin name="GPIO2" x="-22.86" y="5.08" length="middle"/>
<pin name="CH_PD" x="-22.86" y="2.54" length="middle"/>
<pin name="GPIO0" x="-22.86" y="0" length="middle"/>
<pin name="RST" x="-22.86" y="-2.54" length="middle"/>
<pin name="URXD" x="-22.86" y="-5.08" length="middle"/>
<pin name="VCC" x="-22.86" y="-7.62" length="middle" direction="pwr"/>
<wire x1="-17.78" y1="12.7" x2="5.08" y2="12.7" width="0.254" layer="94"/>
<wire x1="5.08" y1="12.7" x2="17.78" y2="12.7" width="0.254" layer="94"/>
<wire x1="17.78" y1="12.7" x2="17.78" y2="-10.16" width="0.254" layer="94"/>
<wire x1="17.78" y1="-10.16" x2="5.08" y2="-10.16" width="0.254" layer="94"/>
<wire x1="5.08" y1="-10.16" x2="-17.78" y2="-10.16" width="0.254" layer="94"/>
<wire x1="-17.78" y1="-10.16" x2="-17.78" y2="12.7" width="0.254" layer="94"/>
<wire x1="5.08" y1="12.7" x2="5.08" y2="-10.16" width="0.254" layer="94"/>
<text x="11.43" y="1.27" size="2.54" layer="94" rot="R90" align="center">ANTENNA</text>
<text x="-17.78" y="17.78" size="1.778" layer="95">&gt;NAME</text>
<text x="-17.78" y="15.24" size="1.778" layer="96">&gt;VALUE</text>
</symbol>
<symbol name="ULTRASONIC-HC-SR04">
<description>&lt;b&gt;Ultrasonic Ranging Module HC-SR04&lt;/b&gt;</description>
<pin name="VCC" x="-2.54" y="-15.24" length="middle" direction="pwr" rot="R90"/>
<pin name="TRIG" x="0" y="-15.24" length="middle" direction="in" rot="R90"/>
<pin name="ECHO" x="2.54" y="-15.24" length="middle" direction="out" rot="R90"/>
<pin name="GND" x="5.08" y="-15.24" length="middle" direction="pwr" rot="R90"/>
<wire x1="-22.86" y1="-10.16" x2="-22.86" y2="10.16" width="0.254" layer="94"/>
<wire x1="-22.86" y1="10.16" x2="25.4" y2="10.16" width="0.254" layer="94"/>
<wire x1="25.4" y1="10.16" x2="25.4" y2="-10.16" width="0.254" layer="94"/>
<wire x1="25.4" y1="-10.16" x2="-22.86" y2="-10.16" width="0.254" layer="94"/>
<circle x="-12.7" y="0" radius="7.62" width="0.254" layer="94"/>
<circle x="15.24" y="0" radius="7.62" width="0.254" layer="94"/>
<circle x="15.24" y="0" radius="3.81845625" width="0.254" layer="94"/>
<circle x="-12.7" y="0" radius="3.81845625" width="0.254" layer="94"/>
<text x="-22.86" y="15.24" size="1.778" layer="95">&gt;NAME</text>
<text x="-22.86" y="12.7" size="1.778" layer="95">&gt;VALUE</text>
</symbol>
<symbol name="WIRELESS-BLUETOOTH-HC-05">
<description>&lt;b&gt;Bluetooth Transceiver Module&lt;/b&gt; based on &lt;b&gt;HC-05&lt;/b&gt; board</description>
<pin name="STATE" x="-20.32" y="5.08" length="middle"/>
<wire x1="15.24" y1="7.62" x2="15.24" y2="-10.16" width="0.254" layer="94"/>
<wire x1="15.24" y1="-10.16" x2="-15.24" y2="-10.16" width="0.254" layer="94"/>
<wire x1="-15.24" y1="-10.16" x2="-15.24" y2="7.62" width="0.254" layer="94"/>
<wire x1="-15.24" y1="7.62" x2="15.24" y2="7.62" width="0.254" layer="94"/>
<text x="-15.24" y="12.7" size="1.778" layer="95">&gt;NAME</text>
<text x="-15.24" y="10.16" size="1.778" layer="96">&gt;VALUE</text>
<pin name="RX" x="-20.32" y="2.54" length="middle"/>
<pin name="TX" x="-20.32" y="0" length="middle"/>
<pin name="GND" x="-20.32" y="-2.54" length="middle" direction="pwr"/>
<pin name="+5V" x="-20.32" y="-5.08" length="middle" direction="pwr"/>
<pin name="EN" x="-20.32" y="-7.62" length="middle"/>
</symbol>
<symbol name="DC-DC-STEP-DOWN-LM2596">
<description>&lt;b&gt;DC/DC Step-Down Regulator&lt;/b&gt; based on &lt;b&gt;LM2596-ADJ&lt;/b&gt; chip</description>
<pin name="IN+" x="-17.78" y="5.08" visible="pin" length="middle"/>
<pin name="IN-" x="-17.78" y="-5.08" visible="pin" length="middle"/>
<pin name="OUT+" x="17.78" y="5.08" visible="pin" length="middle" rot="R180"/>
<pin name="OUT-" x="17.78" y="-5.08" visible="pin" length="middle" rot="R180"/>
<wire x1="-12.7" y1="10.16" x2="12.7" y2="10.16" width="0.254" layer="94"/>
<wire x1="12.7" y1="10.16" x2="12.7" y2="-10.16" width="0.254" layer="94"/>
<wire x1="12.7" y1="-10.16" x2="-12.7" y2="-10.16" width="0.254" layer="94"/>
<wire x1="-12.7" y1="-10.16" x2="-12.7" y2="10.16" width="0.254" layer="94"/>
<text x="-12.7" y="15.24" size="1.778" layer="95">&gt;NAME</text>
<text x="-12.7" y="12.7" size="1.778" layer="96">&gt;VALUE</text>
</symbol>
</symbols>
<devicesets>
<deviceset name="WIRELESS-WIFI-ESP-01">
<description>&lt;b&gt;Wireless Wi-Fi ESP-01 Module&lt;/b&gt; based on &lt;b&gt;ESP8266&lt;/b&gt; chip
&lt;p&gt;&lt;b&gt;&lt;a href="http://www.ebay.com/sch/esp8266+esp+01+transceiver"&gt;Click here to find device on ebay.com&lt;/a&gt;&lt;/b&gt;&lt;/p&gt;

&lt;p&gt;&lt;img alt="photo" src="http://www.diymodules.org/img/device-photo.php?name=WIRELESS-WIFI-ESP-01"&gt;&lt;/p&gt;</description>
<gates>
<gate name="G$1" symbol="WIRELESS-WIFI-ESP-01" x="0" y="0"/>
</gates>
<devices>
<device name="" package="WIRELESS-WIFI-ESP-01">
<connects>
<connect gate="G$1" pin="CH_PD" pad="B2"/>
<connect gate="G$1" pin="GND" pad="A1"/>
<connect gate="G$1" pin="GPIO0" pad="C1"/>
<connect gate="G$1" pin="GPIO2" pad="B1"/>
<connect gate="G$1" pin="RST" pad="C2"/>
<connect gate="G$1" pin="URXD" pad="D1"/>
<connect gate="G$1" pin="UTXD" pad="A2"/>
<connect gate="G$1" pin="VCC" pad="D2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="ULTRASONIC-HC-SR04">
<description>&lt;b&gt;Ultrasonic Ranging Module HC-SR04&lt;/b&gt;
&lt;p&gt;More details available here:&lt;br&gt;
&lt;a href="http://randomnerdtutorials.com/complete-guide-for-ultrasonic-sensor-hc-sr04/"&gt;
http://randomnerdtutorials.com/complete-guide-for-ultrasonic-sensor-hc-sr04/&lt;/a&gt;&lt;/p&gt;
&lt;p&gt;&lt;b&gt;&lt;a href="http://www.ebay.com/sch/hc+sr04+ultrasonic"&gt;Click here to find device on ebay.com&lt;/a&gt;&lt;/b&gt;&lt;/p&gt;

&lt;p&gt;&lt;img alt="photo" src="http://www.diymodules.org/img/device-photo.php?name=ULTRASONIC-HC-SR04"&gt;&lt;/p&gt;</description>
<gates>
<gate name="G$1" symbol="ULTRASONIC-HC-SR04" x="0" y="0"/>
</gates>
<devices>
<device name="" package="ULTRASONIC-HC-SR04">
<connects>
<connect gate="G$1" pin="ECHO" pad="3"/>
<connect gate="G$1" pin="GND" pad="4"/>
<connect gate="G$1" pin="TRIG" pad="2"/>
<connect gate="G$1" pin="VCC" pad="1"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="#V" package="ULTRASONIC-HC-SR04#V">
<connects>
<connect gate="G$1" pin="ECHO" pad="3"/>
<connect gate="G$1" pin="GND" pad="4"/>
<connect gate="G$1" pin="TRIG" pad="2"/>
<connect gate="G$1" pin="VCC" pad="1"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="WIRELESS-BLUETOOTH-HC-05">
<description>&lt;b&gt;Bluetooth Transceiver Module&lt;/b&gt; based on &lt;b&gt;HC-05&lt;/b&gt; board
&lt;p&gt;Tutorial is available here:&lt;br /&gt;
&lt;a href="https://arduino-info.wikispaces.com/BlueTooth-HC05-HC06-Modules-How-To"&gt;https://arduino-info.wikispaces.com/BlueTooth-HC05-HC06-Modules-How-To&lt;/a&gt;&lt;/p&gt;
&lt;p&gt;&lt;b&gt;&lt;a href="http://www.ebay.com/sch/hc-05+module+rs232"&gt;Click here to find device on ebay.com&lt;/a&gt;&lt;/b&gt;&lt;/p&gt;
&lt;p&gt;&lt;img alt="photo" src="http://www.diymodules.org/img/device-photo.php?name=WIRELESS-BLUETOOTH-HC-05"&gt;&lt;/p&gt;</description>
<gates>
<gate name="G$1" symbol="WIRELESS-BLUETOOTH-HC-05" x="0" y="0"/>
</gates>
<devices>
<device name="" package="WIRELESS-BLUETOOTH-HC-05">
<connects>
<connect gate="G$1" pin="+5V" pad="5"/>
<connect gate="G$1" pin="EN" pad="6"/>
<connect gate="G$1" pin="GND" pad="4"/>
<connect gate="G$1" pin="RX" pad="2"/>
<connect gate="G$1" pin="STATE" pad="1"/>
<connect gate="G$1" pin="TX" pad="3"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="DC-DC-STEP-DOWN-LM2596">
<description>&lt;b&gt;DC/DC Step-Down Regulator&lt;/b&gt; based on &lt;b&gt;LM2596-ADJ&lt;/b&gt; chip
&lt;p&gt;&lt;b&gt;LM2596&lt;/b&gt; datasheet available here:&lt;br /&gt;&lt;a href="http://www.ti.com/lit/ds/symlink/lm2596.pdf"&gt;http://www.ti.com/lit/ds/symlink/lm2596.pdf&lt;/a&gt;&lt;/p&gt;
&lt;p&gt;&lt;b&gt;&lt;a href="http://www.ebay.com/sch/lm2596+power+regulator"&gt;Click here to find device on ebay.com&lt;/a&gt;&lt;/b&gt;&lt;/p&gt;

&lt;p&gt;&lt;img alt="photo" src="http://www.diymodules.org/img/device-photo.php?name=DC-DC-STEP-DOWN-LM2596"&gt;&lt;/p&gt;</description>
<gates>
<gate name="G$1" symbol="DC-DC-STEP-DOWN-LM2596" x="0" y="0"/>
</gates>
<devices>
<device name="" package="DC-DC-STEP-DOWN-LM2596">
<connects>
<connect gate="G$1" pin="IN+" pad="IN+"/>
<connect gate="G$1" pin="IN-" pad="IN-"/>
<connect gate="G$1" pin="OUT+" pad="OUT+"/>
<connect gate="G$1" pin="OUT-" pad="OUT-"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="gy-63">
<packages>
<package name="GY-63">
<pad name="SDA" x="-8.89" y="1.27" drill="0.8" diameter="1.778" shape="long"/>
<pad name="CSB" x="-8.89" y="-1.27" drill="0.8" diameter="1.778" shape="long"/>
<pad name="SCL" x="-8.89" y="3.81" drill="0.8" diameter="1.778" shape="long"/>
<pad name="GND" x="-8.89" y="6.35" drill="0.8" diameter="1.778" shape="long"/>
<pad name="VCC" x="-8.89" y="8.89" drill="0.8" diameter="1.778" shape="long"/>
<pad name="SDO" x="-8.89" y="-3.81" drill="0.8" diameter="1.778" shape="long"/>
<pad name="PS" x="-8.89" y="-6.35" drill="0.8" diameter="1.778" shape="long"/>
<wire x1="-11.43" y1="10.795" x2="4.445" y2="10.795" width="0.127" layer="21"/>
<wire x1="4.445" y1="10.795" x2="4.445" y2="-8.89" width="0.127" layer="21"/>
<wire x1="4.445" y1="-8.89" x2="-11.43" y2="-8.89" width="0.127" layer="21"/>
<wire x1="-11.43" y1="-8.89" x2="-11.43" y2="10.795" width="0.127" layer="21"/>
<text x="2.54" y="0" size="1.27" layer="21" rot="R90">MS5611</text>
</package>
</packages>
<symbols>
<symbol name="MS5611">
<wire x1="-10.16" y1="17.78" x2="-10.16" y2="-17.78" width="0.6096" layer="94"/>
<wire x1="-10.16" y1="-17.78" x2="17.78" y2="-17.78" width="0.6096" layer="94"/>
<wire x1="17.78" y1="-17.78" x2="17.78" y2="17.78" width="0.6096" layer="94"/>
<wire x1="17.78" y1="17.78" x2="-10.16" y2="17.78" width="0.6096" layer="94"/>
<text x="13.716" y="-9.398" size="1.778" layer="94" rot="R270">GY-63</text>
<text x="15.24" y="-7.62" size="1.778" layer="94" rot="R90">MS5611</text>
<pin name="VCC" x="-15.24" y="15.24" length="middle"/>
<pin name="GND" x="-15.24" y="10.16" length="middle"/>
<pin name="SCL" x="-15.24" y="5.08" length="middle"/>
<pin name="SDA" x="-15.24" y="0" length="middle"/>
<pin name="CSB" x="-15.24" y="-5.08" length="middle"/>
<pin name="SDO" x="-15.24" y="-10.16" length="middle"/>
<pin name="PS" x="-15.24" y="-15.24" length="middle"/>
<text x="-1.524" y="14.732" size="1.778" layer="94">3.3V (or 5v)</text>
</symbol>
</symbols>
<devicesets>
<deviceset name="GY-63" prefix="U">
<gates>
<gate name="G$1" symbol="MS5611" x="-2.54" y="5.08"/>
</gates>
<devices>
<device name="MS5611" package="GY-63">
<connects>
<connect gate="G$1" pin="CSB" pad="CSB"/>
<connect gate="G$1" pin="GND" pad="GND"/>
<connect gate="G$1" pin="PS" pad="PS"/>
<connect gate="G$1" pin="SCL" pad="SCL"/>
<connect gate="G$1" pin="SDA" pad="SDA"/>
<connect gate="G$1" pin="SDO" pad="SDO"/>
<connect gate="G$1" pin="VCC" pad="VCC"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="gy-521">
<packages>
<package name="GY-521">
<pad name="SDA" x="-8.89" y="1.27" drill="0.8" diameter="1.778" shape="long"/>
<pad name="XDA" x="-8.89" y="-1.27" drill="0.8" diameter="1.778" shape="long"/>
<pad name="SCL" x="-8.89" y="3.81" drill="0.8" diameter="1.778" shape="long"/>
<pad name="GND" x="-8.89" y="6.35" drill="0.8" diameter="1.778" shape="long"/>
<pad name="VCC" x="-8.89" y="8.89" drill="0.8" diameter="1.778" shape="long"/>
<pad name="XCL" x="-8.89" y="-3.81" drill="0.8" diameter="1.778" shape="long"/>
<pad name="ADO" x="-8.89" y="-6.35" drill="0.8" diameter="1.778" shape="long"/>
<pad name="INT" x="-8.89" y="-8.89" drill="0.8" diameter="1.778" shape="long"/>
<wire x1="-11.43" y1="10.795" x2="4.445" y2="10.795" width="0.127" layer="21"/>
<wire x1="4.445" y1="10.795" x2="4.445" y2="-10.16" width="0.127" layer="21"/>
<wire x1="4.445" y1="-10.16" x2="-11.43" y2="-10.16" width="0.127" layer="21"/>
<wire x1="-11.43" y1="-10.16" x2="-11.43" y2="10.795" width="0.127" layer="21"/>
<wire x1="-2.54" y1="-8.89" x2="1.27" y2="-8.89" width="0.127" layer="21"/>
<wire x1="1.27" y1="-8.89" x2="0.635" y2="-8.255" width="0.127" layer="21"/>
<wire x1="1.27" y1="-8.89" x2="0.635" y2="-9.525" width="0.127" layer="21"/>
<wire x1="-2.54" y1="-8.89" x2="-2.54" y2="-5.08" width="0.127" layer="21"/>
<wire x1="-2.54" y1="-5.08" x2="-1.905" y2="-5.715" width="0.127" layer="21"/>
<wire x1="-2.54" y1="-5.08" x2="-3.175" y2="-5.715" width="0.127" layer="21"/>
<text x="1.905" y="-8.89" size="1.27" layer="21">x</text>
<text x="-1.27" y="-5.08" size="1.27" layer="21">y</text>
<text x="3.81" y="-1.27" size="1.27" layer="21" rot="R90">ITG/MPU</text>
</package>
</packages>
<symbols>
<symbol name="MPU6050">
<wire x1="-10.16" y1="17.78" x2="-10.16" y2="-22.86" width="0.6096" layer="94"/>
<wire x1="-10.16" y1="-22.86" x2="17.78" y2="-22.86" width="0.6096" layer="94"/>
<wire x1="17.78" y1="-22.86" x2="17.78" y2="17.78" width="0.6096" layer="94"/>
<wire x1="17.78" y1="17.78" x2="-10.16" y2="17.78" width="0.6096" layer="94"/>
<text x="13.716" y="-9.398" size="1.778" layer="94" rot="R270">GY-521</text>
<text x="15.24" y="-7.62" size="1.778" layer="94" rot="R90">ITG/MPU</text>
<pin name="VCC" x="-15.24" y="15.24" length="middle"/>
<pin name="GND" x="-15.24" y="10.16" length="middle"/>
<pin name="SCL" x="-15.24" y="5.08" length="middle"/>
<pin name="SDA" x="-15.24" y="0" length="middle"/>
<pin name="XDA" x="-15.24" y="-5.08" length="middle"/>
<pin name="XCL" x="-15.24" y="-10.16" length="middle"/>
<pin name="ADO" x="-15.24" y="-15.24" length="middle"/>
<pin name="INT" x="-15.24" y="-20.32" length="middle"/>
<wire x1="2.54" y1="-20.32" x2="7.62" y2="-20.32" width="0.3048" layer="94"/>
<wire x1="7.62" y1="-20.32" x2="6.35" y2="-19.05" width="0.3048" layer="94"/>
<wire x1="7.62" y1="-20.32" x2="6.35" y2="-21.59" width="0.3048" layer="94"/>
<wire x1="2.54" y1="-20.32" x2="2.54" y2="-15.24" width="0.3048" layer="94"/>
<wire x1="2.54" y1="-15.24" x2="1.27" y2="-16.51" width="0.3048" layer="94"/>
<wire x1="2.54" y1="-15.24" x2="3.81" y2="-16.51" width="0.3048" layer="94"/>
<text x="8.89" y="-21.082" size="1.778" layer="94">x</text>
<text x="5.08" y="-15.24" size="1.778" layer="94">y</text>
<text x="-1.524" y="14.732" size="1.778" layer="94">3.3V (or 5v)</text>
</symbol>
</symbols>
<devicesets>
<deviceset name="GY-521" prefix="U">
<gates>
<gate name="G$1" symbol="MPU6050" x="-2.54" y="5.08"/>
</gates>
<devices>
<device name="MPU6050" package="GY-521">
<connects>
<connect gate="G$1" pin="ADO" pad="ADO"/>
<connect gate="G$1" pin="GND" pad="GND"/>
<connect gate="G$1" pin="INT" pad="INT"/>
<connect gate="G$1" pin="SCL" pad="SCL"/>
<connect gate="G$1" pin="SDA" pad="SDA"/>
<connect gate="G$1" pin="VCC" pad="VCC"/>
<connect gate="G$1" pin="XCL" pad="XCL"/>
<connect gate="G$1" pin="XDA" pad="XDA"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="hc12_433mhz">
<packages>
<package name="HC-12_FOOTPRINT">
<smd name="VCC" x="-1.27" y="10.16" dx="1.4224" dy="0.7112" layer="1"/>
<smd name="GND" x="-1.27" y="7.62" dx="1.4224" dy="0.7112" layer="1"/>
<smd name="RXD" x="-1.27" y="5.08" dx="1.4224" dy="0.7112" layer="1"/>
<smd name="TXD" x="-1.27" y="2.54" dx="1.4224" dy="0.7112" layer="1"/>
<smd name="SET" x="-1.27" y="0" dx="1.4224" dy="0.7112" layer="1"/>
<smd name="MCHFIX" x="24.78" y="0.25" dx="1.778" dy="0.9144" layer="1" roundness="100"/>
<smd name="GND1" x="26.13" y="9.57" dx="1.4224" dy="0.7112" layer="1" roundness="100"/>
<smd name="GND2" x="26.13" y="4.49" dx="1.4224" dy="0.7112" layer="1" roundness="100"/>
<smd name="ANT" x="25.49" y="7.03" dx="2.54" dy="1.27" layer="1"/>
</package>
</packages>
<symbols>
<symbol name="HC-12_FOOTPRINT">
<pin name="VCC" x="-22.86" y="7.62" length="middle"/>
<pin name="GND" x="-22.86" y="5.08" length="middle"/>
<pin name="RX" x="-22.86" y="2.54" length="middle"/>
<pin name="TX" x="-22.86" y="0" length="middle"/>
<pin name="SET" x="-22.86" y="-2.54" length="middle"/>
<wire x1="-17.78" y1="12.7" x2="-17.78" y2="-7.62" width="0.254" layer="94"/>
<wire x1="-17.78" y1="-7.62" x2="17.78" y2="-7.62" width="0.254" layer="94"/>
<wire x1="17.78" y1="-7.62" x2="17.78" y2="12.7" width="0.254" layer="94"/>
<wire x1="17.78" y1="12.7" x2="-17.78" y2="12.7" width="0.254" layer="94"/>
<pin name="ANT" x="22.86" y="2.54" length="middle" rot="R180"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="HC-12_FOOTPRINT">
<description>&lt;b&gt;HC-12 433MHz module footprint&lt;/b&gt;
&lt;p&gt;MCHFIX is for mechanical fix pin which is NC but on this file connected to GND&lt;/p&gt;

&lt;p&gt;https://github.com/meendiz/hc-12_si4463/&lt;/p&gt;</description>
<gates>
<gate name="G$1" symbol="HC-12_FOOTPRINT" x="0" y="-2.54"/>
</gates>
<devices>
<device name="" package="HC-12_FOOTPRINT">
<connects>
<connect gate="G$1" pin="ANT" pad="ANT"/>
<connect gate="G$1" pin="GND" pad="GND GND1 GND2 MCHFIX"/>
<connect gate="G$1" pin="RX" pad="RXD"/>
<connect gate="G$1" pin="SET" pad="SET"/>
<connect gate="G$1" pin="TX" pad="TXD"/>
<connect gate="G$1" pin="VCC" pad="VCC"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="u_block_M8">
<packages>
<package name="U-BLOX">
<wire x1="-15.24" y1="12.065" x2="5.715" y2="12.065" width="0.127" layer="21"/>
<wire x1="5.715" y1="12.065" x2="5.715" y2="-11.43" width="0.127" layer="21"/>
<wire x1="5.715" y1="-11.43" x2="-15.24" y2="-11.43" width="0.127" layer="21"/>
<wire x1="-15.24" y1="-11.43" x2="-15.24" y2="12.065" width="0.127" layer="21"/>
<wire x1="-6.76" y1="-10.07" x2="-6.76" y2="2.33" width="0.127" layer="21"/>
<wire x1="-6.76" y1="2.33" x2="-12.51" y2="2.33" width="0.127" layer="21"/>
<wire x1="-12.51" y1="2.33" x2="-12.51" y2="-10.07" width="0.127" layer="21"/>
<wire x1="-12.51" y1="-10.07" x2="-6.76" y2="-10.07" width="0.127" layer="21"/>
<wire x1="-12.76" y1="-10.32" x2="-12.76" y2="2.58" width="0.05" layer="39"/>
<wire x1="-12.76" y1="2.58" x2="-6.51" y2="2.58" width="0.05" layer="39"/>
<wire x1="-6.51" y1="2.58" x2="-6.51" y2="-10.32" width="0.05" layer="39"/>
<wire x1="-6.51" y1="-10.32" x2="-12.76" y2="-10.32" width="0.05" layer="39"/>
<text x="-13.44396875" y="-10.16306875" size="1.272290625" layer="25" rot="R90">&gt;M8_GPS</text>
<wire x1="-6.76" y1="-10.07" x2="-6.76" y2="2.33" width="0.127" layer="51"/>
<wire x1="-6.76" y1="2.33" x2="-12.51" y2="2.33" width="0.127" layer="51"/>
<wire x1="-12.51" y1="2.33" x2="-12.51" y2="-10.07" width="0.127" layer="51"/>
<wire x1="-12.51" y1="-10.07" x2="-6.76" y2="-10.07" width="0.127" layer="51"/>
<circle x="-10.16" y="-10.68" radius="0.1" width="0.2" layer="21"/>
<pad name="GND" x="-10.16" y="-7.62" drill="1.06" shape="square" rot="R90"/>
<pad name="U_TX" x="-10.16" y="-5.12" drill="1.06" rot="R90"/>
<pad name="U_RX" x="-10.16" y="-2.62" drill="1.06" rot="R90"/>
<pad name="VCC" x="-10.16" y="-0.12" drill="1.06" rot="R90"/>
<wire x1="-3.7" y1="3.475" x2="-3.7" y2="9.225" width="0.127" layer="51"/>
<wire x1="-3.7" y1="9.225" x2="3.7" y2="9.225" width="0.127" layer="51"/>
<wire x1="3.7" y1="9.225" x2="3.7" y2="3.475" width="0.127" layer="51"/>
<wire x1="3.7" y1="3.475" x2="-3.7" y2="3.475" width="0.127" layer="51"/>
<wire x1="-3.7" y1="3.475" x2="-3.7" y2="9.225" width="0.127" layer="21"/>
<wire x1="-3.7" y1="9.225" x2="3.7" y2="9.225" width="0.127" layer="21"/>
<wire x1="3.7" y1="9.225" x2="3.7" y2="3.475" width="0.127" layer="21"/>
<wire x1="3.7" y1="3.475" x2="-3.7" y2="3.475" width="0.127" layer="21"/>
<wire x1="-3.95" y1="3.225" x2="-3.95" y2="9.475" width="0.05" layer="39"/>
<wire x1="-3.95" y1="9.475" x2="3.95" y2="9.475" width="0.05" layer="39"/>
<wire x1="3.95" y1="9.475" x2="3.95" y2="3.225" width="0.05" layer="39"/>
<wire x1="3.95" y1="3.225" x2="-3.95" y2="3.225" width="0.05" layer="39"/>
<text x="-5.22" y="9.55" size="1.27" layer="25">&gt;HMC5883L</text>
<circle x="-1.25" y="2.85" radius="0.1" width="0.2" layer="21"/>
<circle x="-1.25" y="2.85" radius="0.1" width="0.2" layer="51"/>
<pad name="SCL" x="-1.25" y="5.825" drill="1" shape="square"/>
<pad name="SDA" x="1.25" y="5.825" drill="1"/>
<text x="0" y="-8.89" size="1.27" layer="21" rot="R90">U-blox-M8</text>
</package>
</packages>
<symbols>
<symbol name="U-BLOX">
<wire x1="-10.16" y1="17.78" x2="-10.16" y2="-12.7" width="0.6096" layer="94"/>
<wire x1="-10.16" y1="-12.7" x2="17.78" y2="-12.7" width="0.6096" layer="94"/>
<wire x1="17.78" y1="-12.7" x2="17.78" y2="17.78" width="0.6096" layer="94"/>
<wire x1="17.78" y1="17.78" x2="-10.16" y2="17.78" width="0.6096" layer="94"/>
<text x="13.716" y="13.462" size="1.778" layer="94" rot="R270">M8-GPS</text>
<text x="15.24" y="-10.16" size="1.778" layer="94" rot="R90">HMC5883L</text>
<pin name="VCC" x="-15.24" y="15.24" length="middle"/>
<pin name="GND" x="-15.24" y="10.16" length="middle"/>
<pin name="UART_TX" x="-15.24" y="5.08" length="middle"/>
<pin name="UART_RX" x="-15.24" y="0" length="middle"/>
<pin name="SCL" x="-15.24" y="-5.08" length="middle"/>
<pin name="SDA" x="-15.24" y="-10.16" length="middle"/>
<text x="-1.524" y="14.732" size="1.778" layer="94">3.3V (or 5v)</text>
</symbol>
</symbols>
<devicesets>
<deviceset name="GY-63" prefix="U">
<gates>
<gate name="G$1" symbol="U-BLOX" x="-2.54" y="5.08"/>
</gates>
<devices>
<device name="MS5611" package="U-BLOX">
<connects>
<connect gate="G$1" pin="GND" pad="GND"/>
<connect gate="G$1" pin="SCL" pad="SCL"/>
<connect gate="G$1" pin="SDA" pad="SDA"/>
<connect gate="G$1" pin="UART_RX" pad="U_RX"/>
<connect gate="G$1" pin="UART_TX" pad="U_TX"/>
<connect gate="G$1" pin="VCC" pad="VCC"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
</libraries>
<attributes>
</attributes>
<variantdefs>
</variantdefs>
<classes>
<class number="0" name="default" width="0" drill="0">
</class>
</classes>
<parts>
<part name="IC1" library="EK-TM4C123GXL" deviceset="EK-TM4C123GXL" device="P"/>
<part name="FRAME1" library="frames" library_urn="urn:adsk.eagle:library:229" deviceset="A3L-LOC" device=""/>
<part name="FRAME2" library="frames" library_urn="urn:adsk.eagle:library:229" deviceset="A3L-LOC" device=""/>
<part name="U$1" library="SIM800L" deviceset="SIM800L" device=""/>
<part name="U$2" library="diy-modules" deviceset="WIRELESS-WIFI-ESP-01" device=""/>
<part name="U$3" library="diy-modules" deviceset="ULTRASONIC-HC-SR04" device=""/>
<part name="U$4" library="diy-modules" deviceset="WIRELESS-BLUETOOTH-HC-05" device=""/>
<part name="U1" library="gy-63" deviceset="GY-63" device="MS5611"/>
<part name="U2" library="gy-521" deviceset="GY-521" device="MPU6050"/>
<part name="U$5" library="hc12_433mhz" deviceset="HC-12_FOOTPRINT" device=""/>
<part name="U3" library="u_block_M8" deviceset="GY-63" device="MS5611"/>
<part name="U$6" library="diy-modules" deviceset="DC-DC-STEP-DOWN-LM2596" device=""/>
</parts>
<sheets>
<sheet>
<description>Quadcopter controller module. It's composed by a Texas EK-TM4C123GXL.</description>
<plain>
<text x="198.12" y="-68.58" size="2.54" layer="91">Quadcopter Controller Board.
Author: Fernando Fontes</text>
</plain>
<instances>
<instance part="IC1" gate="G$1" x="73.66" y="63.5" smashed="yes">
<attribute name="NAME" x="43.1433" y="80.0299" size="1.780140625" layer="95"/>
<attribute name="VALUE" x="43.1671" y="45.7125" size="1.77875" layer="96"/>
</instance>
<instance part="FRAME1" gate="G$1" x="-93.98" y="-78.74" smashed="yes">
<attribute name="DRAWING_NAME" x="250.19" y="-63.5" size="2.54" layer="94"/>
<attribute name="LAST_DATE_TIME" x="250.19" y="-68.58" size="2.286" layer="94"/>
<attribute name="SHEET" x="263.525" y="-73.66" size="2.54" layer="94"/>
</instance>
</instances>
<busses>
</busses>
<nets>
<net name="5V0" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="+5V"/>
<wire x1="60.96" y1="73.66" x2="66.04" y2="73.66" width="0.1524" layer="91"/>
<label x="66.04" y="73.66" size="1.016" layer="95" xref="yes"/>
</segment>
</net>
<net name="3V3" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="+3.3V"/>
<wire x1="38.1" y1="73.66" x2="33.02" y2="73.66" width="0.1524" layer="91"/>
<label x="33.02" y="73.66" size="1.016" layer="95" rot="R180" xref="yes"/>
</segment>
</net>
<net name="GND" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="GND"/>
<wire x1="60.96" y1="71.12" x2="66.04" y2="71.12" width="0.1524" layer="91"/>
<label x="66.04" y="71.12" size="1.016" layer="95" xref="yes"/>
</segment>
</net>
<net name="SPI_SCK_3" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PD0"/>
<wire x1="60.96" y1="68.58" x2="66.04" y2="68.58" width="0.1524" layer="91"/>
<label x="66.04" y="68.58" size="1.016" layer="95" xref="yes"/>
</segment>
</net>
<net name="SPI_CS_3" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PD1"/>
<wire x1="60.96" y1="66.04" x2="66.04" y2="66.04" width="0.1524" layer="91"/>
<label x="66.04" y="66.04" size="1.016" layer="95" xref="yes"/>
</segment>
</net>
<net name="SPI_MISO_3" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PD2"/>
<wire x1="60.96" y1="63.5" x2="66.04" y2="63.5" width="0.1524" layer="91"/>
<label x="66.04" y="63.5" size="1.016" layer="95" xref="yes"/>
</segment>
</net>
<net name="SPI_MOSI_3" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PD3"/>
<wire x1="60.96" y1="60.96" x2="66.04" y2="60.96" width="0.1524" layer="91"/>
<label x="66.04" y="60.96" size="1.016" layer="95" xref="yes"/>
</segment>
</net>
<net name="U7_TX" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PE1"/>
<wire x1="60.96" y1="58.42" x2="66.04" y2="58.42" width="0.1524" layer="91"/>
<label x="66.04" y="58.42" size="1.016" layer="95" xref="yes"/>
</segment>
</net>
<net name="PE2" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PE2"/>
<wire x1="60.96" y1="55.88" x2="66.04" y2="55.88" width="0.1524" layer="91"/>
<label x="66.04" y="55.88" size="1.016" layer="95" xref="yes"/>
</segment>
</net>
<net name="A0" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PE3"/>
<wire x1="60.96" y1="53.34" x2="66.04" y2="53.34" width="0.1524" layer="91"/>
<label x="66.04" y="53.34" size="1.016" layer="95" xref="yes"/>
</segment>
</net>
<net name="RED_LED" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PF1"/>
<wire x1="60.96" y1="50.8" x2="66.04" y2="50.8" width="0.1524" layer="91"/>
<label x="66.04" y="50.8" size="1.016" layer="95" xref="yes"/>
</segment>
</net>
<net name="PB5" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PB5"/>
<wire x1="38.1" y1="71.12" x2="33.02" y2="71.12" width="0.1524" layer="91"/>
<label x="33.02" y="71.12" size="1.016" layer="95" rot="R180" xref="yes"/>
</segment>
</net>
<net name="U1_RX" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PB0"/>
<wire x1="38.1" y1="68.58" x2="33.02" y2="68.58" width="0.1524" layer="91"/>
<label x="33.02" y="68.58" size="1.016" layer="95" rot="R180" xref="yes"/>
</segment>
</net>
<net name="U1_TX" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PB1"/>
<wire x1="38.1" y1="66.04" x2="33.02" y2="66.04" width="0.1524" layer="91"/>
<label x="33.02" y="66.04" size="1.016" layer="95" rot="R180" xref="yes"/>
</segment>
</net>
<net name="U5_RX" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PE4"/>
<wire x1="38.1" y1="63.5" x2="33.02" y2="63.5" width="0.1524" layer="91"/>
<label x="33.02" y="63.5" size="1.016" layer="95" rot="R180" xref="yes"/>
</segment>
</net>
<net name="U5_TX" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PE5"/>
<wire x1="38.1" y1="60.96" x2="33.02" y2="60.96" width="0.1524" layer="91"/>
<label x="33.02" y="60.96" size="1.016" layer="95" rot="R180" xref="yes"/>
</segment>
</net>
<net name="ENABLE_0" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PB4"/>
<wire x1="38.1" y1="58.42" x2="33.02" y2="58.42" width="0.1524" layer="91"/>
<label x="33.02" y="58.42" size="1.016" layer="95" rot="R180" xref="yes"/>
</segment>
</net>
<net name="ENABLE_1" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PA5"/>
<wire x1="38.1" y1="55.88" x2="33.02" y2="55.88" width="0.1524" layer="91"/>
<label x="33.02" y="55.88" size="1.016" layer="95" rot="R180" xref="yes"/>
</segment>
</net>
<net name="I2C_SCL_1" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PA6"/>
<wire x1="38.1" y1="53.34" x2="33.02" y2="53.34" width="0.1524" layer="91"/>
<label x="33.02" y="53.34" size="1.016" layer="95" rot="R180" xref="yes"/>
</segment>
</net>
<net name="I2C_SDA_1" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PA7"/>
<wire x1="38.1" y1="50.8" x2="33.02" y2="50.8" width="0.1524" layer="91"/>
<label x="33.02" y="50.8" size="1.016" layer="95" rot="R180" xref="yes"/>
</segment>
</net>
<net name="PB_2" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PB2"/>
<wire x1="121.92" y1="71.12" x2="127" y2="71.12" width="0.1524" layer="91"/>
<label x="127" y="71.12" size="1.016" layer="95" xref="yes"/>
</segment>
</net>
<net name="U7_RX" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PE0"/>
<wire x1="121.92" y1="68.58" x2="127" y2="68.58" width="0.1524" layer="91"/>
<label x="127" y="68.58" size="1.016" layer="95" xref="yes"/>
</segment>
</net>
<net name="PUSH2" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PF0"/>
<wire x1="121.92" y1="66.04" x2="127" y2="66.04" width="0.1524" layer="91"/>
<label x="127" y="66.04" size="1.016" layer="95" xref="yes"/>
</segment>
</net>
<net name="RESET" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="RESET"/>
<wire x1="121.92" y1="63.5" x2="127" y2="63.5" width="0.1524" layer="91"/>
<label x="127" y="63.5" size="1.016" layer="95" xref="yes"/>
</segment>
</net>
<net name="ENABLE_6" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PB7"/>
<wire x1="121.92" y1="60.96" x2="127" y2="60.96" width="0.1524" layer="91"/>
<label x="127" y="60.96" size="1.016" layer="95" xref="yes"/>
</segment>
</net>
<net name="ENABLE_5" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PB6"/>
<wire x1="121.92" y1="58.42" x2="127" y2="58.42" width="0.1524" layer="91"/>
<label x="127" y="58.42" size="1.016" layer="95" xref="yes"/>
</segment>
</net>
<net name="PA_4" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PA4"/>
<wire x1="121.92" y1="55.88" x2="127" y2="55.88" width="0.1524" layer="91"/>
<label x="127" y="55.88" size="1.016" layer="95" xref="yes"/>
</segment>
</net>
<net name="PA_3" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PA3"/>
<wire x1="121.92" y1="53.34" x2="127" y2="53.34" width="0.1524" layer="91"/>
<label x="127" y="53.34" size="1.016" layer="95" xref="yes"/>
</segment>
</net>
<net name="PA_2" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PA2"/>
<wire x1="121.92" y1="50.8" x2="127" y2="50.8" width="0.1524" layer="91"/>
<label x="127" y="50.8" size="1.016" layer="95" xref="yes"/>
</segment>
</net>
<net name="BLUE_LED" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PF2"/>
<wire x1="99.06" y1="73.66" x2="93.98" y2="73.66" width="0.1524" layer="91"/>
<label x="93.98" y="73.66" size="1.016" layer="95" rot="R180" xref="yes"/>
</segment>
</net>
<net name="GREEN_LED" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PF3"/>
<wire x1="99.06" y1="71.12" x2="93.98" y2="71.12" width="0.1524" layer="91"/>
<label x="93.98" y="71.12" size="1.016" layer="95" rot="R180" xref="yes"/>
</segment>
</net>
<net name="ENABLE_4" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PB3"/>
<wire x1="99.06" y1="68.58" x2="93.98" y2="68.58" width="0.1524" layer="91"/>
<label x="93.98" y="68.58" size="1.016" layer="95" rot="R180" xref="yes"/>
</segment>
</net>
<net name="ENABLE_3" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PC4"/>
<wire x1="99.06" y1="66.04" x2="93.98" y2="66.04" width="0.1524" layer="91"/>
<label x="93.98" y="66.04" size="1.016" layer="95" rot="R180" xref="yes"/>
</segment>
</net>
<net name="ENABLE_2" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PC5"/>
<wire x1="99.06" y1="63.5" x2="93.98" y2="63.5" width="0.1524" layer="91"/>
<label x="93.98" y="63.5" size="1.016" layer="95" rot="R180" xref="yes"/>
</segment>
</net>
<net name="U3_RX" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PC6"/>
<wire x1="99.06" y1="60.96" x2="93.98" y2="60.96" width="0.1524" layer="91"/>
<label x="93.98" y="60.96" size="1.016" layer="95" rot="R180" xref="yes"/>
</segment>
</net>
<net name="U3_TX" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PC7"/>
<wire x1="99.06" y1="58.42" x2="93.98" y2="58.42" width="0.1524" layer="91"/>
<label x="93.98" y="58.42" size="1.016" layer="95" rot="R180" xref="yes"/>
</segment>
</net>
<net name="U2_RX" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PD6"/>
<wire x1="99.06" y1="55.88" x2="93.98" y2="55.88" width="0.1524" layer="91"/>
<label x="93.98" y="55.88" size="1.016" layer="95" rot="R180" xref="yes"/>
</segment>
</net>
<net name="U2_TX" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PD7"/>
<wire x1="99.06" y1="53.34" x2="93.98" y2="53.34" width="0.1524" layer="91"/>
<label x="93.98" y="53.34" size="1.016" layer="95" rot="R180" xref="yes"/>
</segment>
</net>
<net name="PUSH1" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PF4"/>
<wire x1="99.06" y1="50.8" x2="93.98" y2="50.8" width="0.1524" layer="91"/>
<label x="93.98" y="50.8" size="1.016" layer="95" rot="R180" xref="yes"/>
</segment>
</net>
<net name="GND2" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="GND2"/>
<wire x1="121.92" y1="73.66" x2="127" y2="73.66" width="0.1524" layer="91"/>
<label x="127" y="73.66" size="1.016" layer="95" xref="yes"/>
</segment>
</net>
</nets>
</sheet>
<sheet>
<description>Quadcopter peripherals. It's composed by: ESP-01, HC-05, HC-12, MPU-6050, MS5661, SIM800L, U-BLOX M8 GPS</description>
<plain>
<text x="274.32" y="294.64" size="1.778" layer="91">Needs shift logic from 5 to 3v3</text>
<text x="147.32" y="165.1" size="1.778" layer="91">Needs shift logic from 5 to 3v3</text>
<text x="149.86" y="203.2" size="1.778" layer="91">Connects to 3V3</text>
<text x="144.78" y="304.8" size="1.778" layer="91">Needs shift logic from 5 to 3v3</text>
</plain>
<instances>
<instance part="FRAME2" gate="G$1" x="106.68" y="68.58" smashed="yes">
<attribute name="DRAWING_NAME" x="450.85" y="83.82" size="2.54" layer="94"/>
<attribute name="LAST_DATE_TIME" x="450.85" y="78.74" size="2.286" layer="94"/>
<attribute name="SHEET" x="464.185" y="73.66" size="2.54" layer="94"/>
</instance>
<instance part="U$1" gate="G$1" x="162.56" y="287.02" smashed="yes"/>
<instance part="U$2" gate="G$1" x="162.56" y="218.44" smashed="yes">
<attribute name="NAME" x="144.78" y="236.22" size="1.778" layer="95"/>
<attribute name="VALUE" x="144.78" y="233.68" size="1.778" layer="96"/>
</instance>
<instance part="U$3" gate="G$1" x="297.18" y="274.32" smashed="yes">
<attribute name="NAME" x="274.32" y="289.56" size="1.778" layer="95"/>
<attribute name="VALUE" x="274.32" y="287.02" size="1.778" layer="95"/>
</instance>
<instance part="U$4" gate="G$1" x="162.56" y="147.32" smashed="yes">
<attribute name="NAME" x="147.32" y="160.02" size="1.778" layer="95"/>
<attribute name="VALUE" x="147.32" y="157.48" size="1.778" layer="96"/>
</instance>
<instance part="U1" gate="G$1" x="421.64" y="220.98" smashed="yes"/>
<instance part="U2" gate="G$1" x="421.64" y="144.78" smashed="yes"/>
<instance part="U$5" gate="G$1" x="299.72" y="210.82" smashed="yes"/>
<instance part="U3" gate="G$1" x="297.18" y="152.4" smashed="yes"/>
<instance part="U$6" gate="G$1" x="424.18" y="284.48" smashed="yes">
<attribute name="NAME" x="411.48" y="299.72" size="1.778" layer="95"/>
<attribute name="VALUE" x="411.48" y="297.18" size="1.778" layer="96"/>
</instance>
</instances>
<busses>
</busses>
<nets>
<net name="5V0" class="0">
<segment>
<pinref part="U$4" gate="G$1" pin="+5V"/>
<wire x1="142.24" y1="142.24" x2="134.62" y2="142.24" width="0.1524" layer="91"/>
<label x="134.62" y="142.24" size="1.016" layer="95" rot="R180" xref="yes"/>
</segment>
<segment>
<pinref part="U$6" gate="G$1" pin="OUT+"/>
<wire x1="441.96" y1="289.56" x2="449.58" y2="289.56" width="0.1524" layer="91"/>
<label x="449.58" y="289.56" size="1.016" layer="95" xref="yes"/>
</segment>
<segment>
<pinref part="U1" gate="G$1" pin="VCC"/>
<wire x1="406.4" y1="236.22" x2="398.78" y2="236.22" width="0.1524" layer="91"/>
<label x="398.78" y="236.22" size="1.016" layer="95" rot="R180" xref="yes"/>
</segment>
<segment>
<pinref part="U2" gate="G$1" pin="VCC"/>
<wire x1="406.4" y1="160.02" x2="398.78" y2="160.02" width="0.1524" layer="91"/>
<label x="398.78" y="160.02" size="1.016" layer="95" rot="R180" xref="yes"/>
</segment>
<segment>
<pinref part="U3" gate="G$1" pin="VCC"/>
<wire x1="281.94" y1="167.64" x2="274.32" y2="167.64" width="0.1524" layer="91"/>
<label x="274.32" y="167.64" size="1.016" layer="95" rot="R180" xref="yes"/>
</segment>
<segment>
<pinref part="U$5" gate="G$1" pin="VCC"/>
<wire x1="276.86" y1="218.44" x2="266.7" y2="218.44" width="0.1524" layer="91"/>
<label x="266.7" y="218.44" size="1.016" layer="95" rot="R180" xref="yes"/>
</segment>
<segment>
<pinref part="U$2" gate="G$1" pin="VCC"/>
<wire x1="139.7" y1="210.82" x2="132.08" y2="210.82" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="U$1" gate="G$1" pin="5V"/>
<wire x1="147.32" y1="297.18" x2="142.24" y2="297.18" width="0.1524" layer="91"/>
<label x="142.24" y="297.18" size="1.016" layer="95" rot="R180" xref="yes"/>
</segment>
<segment>
<pinref part="U$3" gate="G$1" pin="VCC"/>
<wire x1="294.64" y1="259.08" x2="294.64" y2="254" width="0.1524" layer="91"/>
<label x="294.64" y="254" size="1.016" layer="95" rot="R270" xref="yes"/>
</segment>
</net>
<net name="N$2" class="0">
<segment>
<pinref part="U$4" gate="G$1" pin="EN"/>
<wire x1="142.24" y1="139.7" x2="134.62" y2="139.7" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$3" class="0">
<segment>
<pinref part="U$4" gate="G$1" pin="TX"/>
<wire x1="142.24" y1="147.32" x2="134.62" y2="147.32" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$4" class="0">
<segment>
<pinref part="U$4" gate="G$1" pin="RX"/>
<wire x1="142.24" y1="149.86" x2="134.62" y2="149.86" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$5" class="0">
<segment>
<pinref part="U$4" gate="G$1" pin="STATE"/>
<wire x1="142.24" y1="152.4" x2="134.62" y2="152.4" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$8" class="0">
<segment>
<pinref part="U3" gate="G$1" pin="UART_TX"/>
<wire x1="281.94" y1="157.48" x2="274.32" y2="157.48" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$9" class="0">
<segment>
<pinref part="U3" gate="G$1" pin="UART_RX"/>
<wire x1="281.94" y1="152.4" x2="274.32" y2="152.4" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$10" class="0">
<segment>
<pinref part="U3" gate="G$1" pin="SCL"/>
<wire x1="281.94" y1="147.32" x2="274.32" y2="147.32" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$11" class="0">
<segment>
<pinref part="U3" gate="G$1" pin="SDA"/>
<wire x1="281.94" y1="142.24" x2="274.32" y2="142.24" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$12" class="0">
<segment>
<pinref part="U$5" gate="G$1" pin="SET"/>
<wire x1="276.86" y1="208.28" x2="266.7" y2="208.28" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$13" class="0">
<segment>
<pinref part="U$5" gate="G$1" pin="TX"/>
<wire x1="276.86" y1="210.82" x2="266.7" y2="210.82" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$14" class="0">
<segment>
<pinref part="U$5" gate="G$1" pin="RX"/>
<wire x1="276.86" y1="213.36" x2="266.7" y2="213.36" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$17" class="0">
<segment>
<pinref part="U$5" gate="G$1" pin="ANT"/>
<wire x1="322.58" y1="213.36" x2="327.66" y2="213.36" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$19" class="0">
<segment>
<pinref part="U$2" gate="G$1" pin="UTXD"/>
<wire x1="139.7" y1="226.06" x2="132.08" y2="226.06" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$20" class="0">
<segment>
<pinref part="U$2" gate="G$1" pin="GPIO2"/>
<wire x1="139.7" y1="223.52" x2="132.08" y2="223.52" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$21" class="0">
<segment>
<pinref part="U$2" gate="G$1" pin="CH_PD"/>
<wire x1="139.7" y1="220.98" x2="132.08" y2="220.98" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$22" class="0">
<segment>
<pinref part="U$2" gate="G$1" pin="GPIO0"/>
<wire x1="139.7" y1="218.44" x2="132.08" y2="218.44" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$23" class="0">
<segment>
<pinref part="U$2" gate="G$1" pin="RST"/>
<wire x1="139.7" y1="215.9" x2="132.08" y2="215.9" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$24" class="0">
<segment>
<pinref part="U$2" gate="G$1" pin="URXD"/>
<wire x1="139.7" y1="213.36" x2="132.08" y2="213.36" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$27" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="VDD"/>
<wire x1="147.32" y1="292.1" x2="142.24" y2="292.1" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$28" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="TXD"/>
<wire x1="147.32" y1="287.02" x2="142.24" y2="287.02" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$30" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="RST"/>
<wire x1="170.18" y1="292.1" x2="177.8" y2="292.1" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$31" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="RXD"/>
<wire x1="170.18" y1="287.02" x2="177.8" y2="287.02" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$33" class="0">
<segment>
<pinref part="U$3" gate="G$1" pin="TRIG"/>
<wire x1="297.18" y1="259.08" x2="297.18" y2="254" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$34" class="0">
<segment>
<pinref part="U$3" gate="G$1" pin="ECHO"/>
<wire x1="299.72" y1="259.08" x2="299.72" y2="254" width="0.1524" layer="91"/>
</segment>
</net>
<net name="VBAT+" class="0">
<segment>
<pinref part="U$6" gate="G$1" pin="IN+"/>
<wire x1="406.4" y1="289.56" x2="398.78" y2="289.56" width="0.1524" layer="91"/>
<label x="398.78" y="289.56" size="1.016" layer="95" rot="R180" xref="yes"/>
</segment>
</net>
<net name="VBAT-" class="0">
<segment>
<pinref part="U$6" gate="G$1" pin="IN-"/>
<wire x1="406.4" y1="279.4" x2="403.86" y2="279.4" width="0.1524" layer="91"/>
<wire x1="403.86" y1="279.4" x2="401.32" y2="279.4" width="0.1524" layer="91"/>
<wire x1="401.32" y1="279.4" x2="398.78" y2="279.4" width="0.1524" layer="91"/>
<label x="398.78" y="279.4" size="1.016" layer="95" rot="R180" xref="yes"/>
</segment>
</net>
<net name="GND" class="0">
<segment>
<pinref part="U$6" gate="G$1" pin="OUT-"/>
<wire x1="441.96" y1="279.4" x2="449.58" y2="279.4" width="0.1524" layer="91"/>
<label x="449.58" y="279.4" size="1.016" layer="95" xref="yes"/>
</segment>
<segment>
<pinref part="U1" gate="G$1" pin="GND"/>
<wire x1="406.4" y1="231.14" x2="398.78" y2="231.14" width="0.1524" layer="91"/>
<label x="398.78" y="231.14" size="1.016" layer="95" rot="R180" xref="yes"/>
</segment>
<segment>
<pinref part="U2" gate="G$1" pin="GND"/>
<wire x1="406.4" y1="154.94" x2="398.78" y2="154.94" width="0.1524" layer="91"/>
<label x="398.78" y="154.94" size="1.016" layer="95" rot="R180" xref="yes"/>
</segment>
<segment>
<pinref part="U3" gate="G$1" pin="GND"/>
<wire x1="281.94" y1="162.56" x2="274.32" y2="162.56" width="0.1524" layer="91"/>
<label x="274.32" y="162.56" size="1.016" layer="95" rot="R180" xref="yes"/>
</segment>
<segment>
<pinref part="U$5" gate="G$1" pin="GND"/>
<wire x1="276.86" y1="215.9" x2="266.7" y2="215.9" width="0.1524" layer="91"/>
<label x="266.7" y="215.9" size="1.016" layer="95" rot="R180" xref="yes"/>
</segment>
<segment>
<pinref part="U$4" gate="G$1" pin="GND"/>
<wire x1="142.24" y1="144.78" x2="134.62" y2="144.78" width="0.1524" layer="91"/>
<label x="134.62" y="144.78" size="1.016" layer="95" rot="R180" xref="yes"/>
</segment>
<segment>
<pinref part="U$2" gate="G$1" pin="GND"/>
<wire x1="139.7" y1="228.6" x2="132.08" y2="228.6" width="0.1524" layer="91"/>
<label x="132.08" y="228.6" size="1.016" layer="95" rot="R180" xref="yes"/>
</segment>
<segment>
<pinref part="U$1" gate="G$1" pin="GND"/>
<wire x1="170.18" y1="297.18" x2="177.8" y2="297.18" width="0.1524" layer="91"/>
<label x="177.8" y="297.18" size="1.016" layer="95" xref="yes"/>
</segment>
<segment>
<pinref part="U$3" gate="G$1" pin="GND"/>
<wire x1="302.26" y1="259.08" x2="302.26" y2="254" width="0.1524" layer="91"/>
<label x="302.26" y="254" size="1.016" layer="95" rot="R270" xref="yes"/>
</segment>
</net>
<net name="N$38" class="0">
<segment>
<pinref part="U1" gate="G$1" pin="SCL"/>
<wire x1="406.4" y1="226.06" x2="398.78" y2="226.06" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$39" class="0">
<segment>
<pinref part="U1" gate="G$1" pin="SDA"/>
<wire x1="406.4" y1="220.98" x2="398.78" y2="220.98" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$40" class="0">
<segment>
<pinref part="U1" gate="G$1" pin="CSB"/>
<wire x1="406.4" y1="215.9" x2="398.78" y2="215.9" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$41" class="0">
<segment>
<pinref part="U1" gate="G$1" pin="SDO"/>
<wire x1="406.4" y1="210.82" x2="398.78" y2="210.82" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$42" class="0">
<segment>
<pinref part="U1" gate="G$1" pin="PS"/>
<wire x1="406.4" y1="205.74" x2="398.78" y2="205.74" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$43" class="0">
<segment>
<pinref part="U2" gate="G$1" pin="SCL"/>
<wire x1="406.4" y1="149.86" x2="398.78" y2="149.86" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$44" class="0">
<segment>
<pinref part="U2" gate="G$1" pin="SDA"/>
<wire x1="406.4" y1="144.78" x2="398.78" y2="144.78" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$45" class="0">
<segment>
<pinref part="U2" gate="G$1" pin="XDA"/>
<wire x1="406.4" y1="139.7" x2="398.78" y2="139.7" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$46" class="0">
<segment>
<pinref part="U2" gate="G$1" pin="XCL"/>
<wire x1="406.4" y1="134.62" x2="398.78" y2="134.62" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$47" class="0">
<segment>
<pinref part="U2" gate="G$1" pin="ADO"/>
<wire x1="406.4" y1="129.54" x2="398.78" y2="129.54" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$48" class="0">
<segment>
<pinref part="U2" gate="G$1" pin="INT"/>
<wire x1="406.4" y1="124.46" x2="398.78" y2="124.46" width="0.1524" layer="91"/>
</segment>
</net>
</nets>
</sheet>
</sheets>
<errors>
<approved hash="209,2,297.18,259.08,N$33,,,,,"/>
<approved hash="209,1,121.92,63.5,RESET,,,,,"/>
</errors>
</schematic>
</drawing>
<compatibility>
<note version="6.3" minversion="6.2.2" severity="warning">
Since Version 6.2.2 text objects can contain more than one line,
which will not be processed correctly with this version.
</note>
<note version="8.2" severity="warning">
Since Version 8.2, EAGLE supports online libraries. The ids
of those online libraries will not be understood (or retained)
with this version.
</note>
<note version="8.3" severity="warning">
Since Version 8.3, EAGLE supports URNs for individual library
assets (packages, symbols, and devices). The URNs of those assets
will not be understood (or retained) with this version.
</note>
</compatibility>
</eagle>
