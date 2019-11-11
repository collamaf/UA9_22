import ROOT

class myStyle(ROOT.TStyle):
    
    def __init__( self, name = "myStyle", title = "Experimental style" ):

        print("Try setting custom style")

        ROOT.TStyle.__init__( self, name, title )
        self.SetName( name )
        self.SetTitle( title )
        self.configure()

        return


    def configure( self ):
        self.Info( "configure", "Configuring custom style" )
       # Use plain black on white colors:
        icol = 0
        self.SetFrameBorderMode( 0 )
        self.SetFrameFillColor( icol )
        self.SetFrameFillStyle( 0 )
        self.SetCanvasBorderMode( 0 )
        self.SetPadBorderMode( 0 )
        self.SetPadColor( icol )
        self.SetCanvasColor( icol )
        self.SetStatColor( icol )

        # Set the paper and margin sizes:
        self.SetPaperSize( 20, 26 )
        self.SetPadTopMargin( 0.07 )
        self.SetPadRightMargin( 0.05 )
        self.SetPadBottomMargin( 0.16 )
        self.SetPadLeftMargin( 0.16 )

        # set title offsets (for axis label)
        self.SetTitleXOffset(1.3);
        self.SetTitleYOffset(1.3);

        # Use large fonts:
        font_type = 42
        font_size = 0.05
        self.SetTextFont( font_type )
        self.SetTextSize( font_size )
        self.SetLegendFont( font_type )
        #self.SetLegendSize( font_size )
        self.SetLabelFont( font_type, "x" )
        self.SetLabelSize( font_size, "x" )
        self.SetTitleFont( font_type, "x" )
        self.SetTitleSize( font_size, "x" )
        self.SetLabelFont( font_type, "y" )
        self.SetLabelSize( font_size, "y" )
        self.SetTitleFont( font_type, "y" )
        self.SetTitleSize( font_size, "y" )
        self.SetLabelFont( font_type, "z" )
        self.SetLabelSize( font_size, "z" )
        self.SetTitleFont( font_type, "z" )
        self.SetTitleSize( font_size, "z" )

        # Use bold lines and markers:
        self.SetMarkerStyle( 20 )
        self.SetMarkerSize( 1.2 )
        self.SetHistLineWidth( 2 )
        self.SetLineStyleString( 2, "[12 12]" )

        # Do not display any of the standard histogram decorations:
        self.SetOptTitle( 0 )
        self.SetOptStat( 0 )
        self.SetOptFit( 0 )

        # Put tick marks on top and rhs of the plots:
        self.SetPadTickX( 1 )
        self.SetPadTickY( 1 )

        return
        


# Tell ROOT to use this style:
style = myStyle()
ROOT.gROOT.SetStyle( style.GetName() )

# Force style applies styles to histograms made under a different style regim
ROOT.gROOT.ForceStyle()
ROOT.gStyle.SetPalette(71)
