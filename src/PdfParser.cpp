#include <iostream>

#include <podofo/podofo.h>

using namespace PoDoFo;

void PDFParser( const char* pszFilename )
{
    
    PdfStreamedDocument document( pszFilename );
    PdfPainter painter;
    PdfPage* pPage;
    PdfFont* pFont;

	try {
		
		pPage = document.CreatePage( PdfPage::CreateStandardPageSize( ePdfPageSize_A4 ) );

		
		if( !pPage )
		{
			PODOFO_RAISE_ERROR( ePdfError_InvalidHandle );
		}

		
		painter.SetPage( pPage );

		
		pFont = document.CreateFont( "Arial" );

		
		if( !pFont )
		{
			PODOFO_RAISE_ERROR( ePdfError_InvalidHandle );
		}

		pFont->SetFontSize( 18.0 );

		painter.SetFont( pFont );

		painter.FinishPage();

		document.Close();
	} catch ( PdfError & e ) {
		
		try {
			painter.FinishPage();
		} catch( ... ) {

		}

		throw e;
	}
}

int main( int argc, char* argv[] )
{
   
    if( argc != 2 )
    {
        PrintHelp();
        return -1;
    }

    try {
        
         PDFParser( argv[1] );
    } catch( PdfError & eCode ) {
        
        eCode.PrintErrorMsg();
        return eCode.GetError();
    }


    try {
        
        PdfEncodingFactory::FreeGlobalEncodingInstances();
    } catch( PdfError & eCode ) {
        
        eCode.PrintErrorMsg();
        return eCode.GetError();
    }

  
    std::cout << std::endl
              << "Created a PDF file " << argv[1] << std::endl;

    return 0;
}
