var projectname;
var projectbrief;

//////////
// Structure

var setUpNavigationBars = function () {
    //////////
    // Get the content of navrow1 (the default 
    // navigation bar in Doxygen) and titlearea, then remove 
    // the top layer of the page
    var content = $('#navrow1').html();
    projectname = $('#projectname').html();
    projectbrief = $('#projectbrief').html();
    $('#top').remove();
    //////////

    //////////
    // Add a proper navigation bar at the top immediatly inside <body></body>
    $('body').prepend('<nav id=navigationbar class="navbar navbar-inverse" role="navigation"> </nav>');
    $('#navigationbar').html(
            '<div class="container-fluid">'
            + '<div class="navbar-header">'
            + '<a class="navbar-brand" href="index.html"><strong>'
            + projectname
            + '</strong></a>'
            + '</div>'
            + '<div>'
            + content
            + '</div>'
            + '</div>'
            );
    $('#navigationbar ul').removeClass('tablist').addClass('nav navbar-nav');
    $('#navigationbar ul li').first().remove();
    //////////

    //////////
    // Set up minor things
    $('#MSearchBox').replaceWith(
            '<form class="navbar-form navbar-left" role="search">'
            + '<div class="form-group">'
            + '<input type="text" class="form-control" placeholder="Still does not work!" onfocus="searchBox.OnSearchFieldFocus(true)" onblur="searchBox.OnSearchFieldFocus(false)" onkeyup="searchBox.OnSearchFieldChange(event)">'
            + '</div>'
            + '</form>'
            );
    //////////

/// TODO: code of the original seach box to be fixed
//    <div id="MSearchBox" class="MSearchBoxInactive">
//        <span class="left">
//          <img id="MSearchSelect" src="search/mag_sel.png" onmouseover="return searchBox.OnSearchSelectShow()" onmouseout="return searchBox.OnSearchSelectHide()" alt="">
//          <input id="MSearchField" value="Search" accesskey="S" onfocus="searchBox.OnSearchFieldFocus(true)" onblur="searchBox.OnSearchFieldFocus(false)" onkeyup="searchBox.OnSearchFieldChange(event)" type="text">
//          </span><span class="right">
//            <a id="MSearchClose" href="javascript:searchBox.CloseResultsWindow()"><img id="MSearchCloseImg" src="search/close.png" alt="" border="0"></a>
//          </span>
//        </div>
};

var setUpContent = function () {
    //////////
    // Set up a generic page title 
    var title = $('div.header > div.headertitle div.title').text();
    $('div.header').replaceWith(
            '<div class="page-header text-center">'
            + '<h1>' + projectname + '<small> ' + projectbrief + ' </small>'
            + '</h1>'
            + '</div>'
            );
    //////////

    //////////
    // Set up page content    
    var content = $('div.contents').html();
    $('div.contents').replaceWith(
            '<div class="container">'
            + '<div id="maincontent" class="jumbotron">'
            + '<h2>' + title + '</h2>'
            + content
            + '</div>'
            + '</div>'
            );
    // Remove silly text auto-generated from doxygen ('Here is ...)
    $('#maincontent div.directory').children().unwrap();
    if ($('#maincontent div.textblock').children().size() !== 0) {
        $('#maincontent div.textblock').children().unwrap();
    } else {
        $('#maincontent div.textblock').remove();
    }
    // Remove doxygen indentation levels 
    $('#maincontent div.levels').remove();
    $('#maincontent span.icona').remove();
    // Tables     
    $('table').addClass('table table-hover').removeClass('directory');
    //$('td.entry').wrapInner('<button type="button" class="btn btn-primary"> </button>');
    //$('td.entry span.arrow').remove();
    $('td.entry span.arrow').replaceWith(
            '<button type="button" class="folder-button btn btn-primary" style="margin : 1em">'
            + '<span class="glyphicon glyphicon-chevron-down" style="font-size : 0.8em;"></span>'
            + '</button>');
    $('td.entry>span').remove();
    $('td.entry a.el').wrapInner('<strong style="font-size : 1.5em;"> </strong>');    
    $('td.desc').addClass('vert-align').wrapInner('<p class="lead"> </p>');
    //////////        
};

var bootstrapDoxygen = function () {
    // Static look
    setUpNavigationBars();
    setUpContent();

    // Expand and collapse namespaces 
    $('button.folder-button').click(function () {
        var id = $(this).parents('tr').attr('id');
        // the clicked row  
        var currentRow = $('#' + id);
        // all rows after the clicked row
        var rows = currentRow.nextAll("tr");
        var re = new RegExp('^' + id + '\\d+_$', "i"); //only one sub
        // only match elements AFTER this one (can't hide elements before)
        var childRows = rows.filter(function () {
            return this.id.match(re);
        });
        // first row is visible we are HIDING
        if (childRows.filter(':first').is(':visible') === true) {
            rows.filter("[id^=" + id + "]").hide(); // hide all children
            $(this).find('span.glyphicon').removeClass('glyphicon-chevron-down').addClass('glyphicon-chevron-right');
        } else { // we are SHOWING
            childRows.show(); //show all children
            $(this).find('span.glyphicon').addClass('glyphicon-chevron-down').removeClass('glyphicon-chevron-right');
            childRows.find('span.glyphicon').removeClass('glyphicon-chevron-down').addClass('glyphicon-chevron-right');            
        }
        updateStripes();        
    });

//	$('li > a[href="index.html"] > span').before("<i class='fa fa-cog'></i> ");
//	$('li > a[href="index.html"] > span').text("CoActionOS");
//	$('li > a[href="modules.html"] > span').before("<i class='fa fa-square'></i> ");
//	$('li > a[href="namespaces.html"] > span').before("<i class='fa fa-bars'></i> ");
//	$('li > a[href="annotated.html"] > span').before("<i class='fa fa-list-ul'></i> ");
//	$('li > a[href="classes.html"] > span').before("<i class='fa fa-book'></i> ");
//	$('li > a[href="inherits.html"] > span').before("<i class='fa fa-sitemap'></i> ");
//	$('li > a[href="functions.html"] > span').before("<i class='fa fa-list'></i> ");
//	$('li > a[href="functions_func.html"] > span').before("<i class='fa fa-list'></i> ");
//	$('li > a[href="functions_vars.html"] > span').before("<i class='fa fa-list'></i> ");
//	$('li > a[href="functions_enum.html"] > span').before("<i class='fa fa-list'></i> ");
//	$('li > a[href="functions_eval.html"] > span').before("<i class='fa fa-list'></i> ");
//	$('img[src="ftv2ns.png"]').replaceWith('<span class="label label-danger">N</span> ');
//	$('img[src="ftv2cl.png"]').replaceWith('<span class="label label-danger">C</span> ');
//	
//	$("ul.tablist").addClass("nav nav-pills nav-justified");
//	$("ul.tablist").css("margin-top", "0.5em");
//	$("ul.tablist").css("margin-bottom", "0.5em");
//	$("li.current").addClass("active");
//	$("iframe").attr("scrolling", "yes");
//	
//	$("#nav-path > ul").addClass("breadcrumb");
//	
//	$("table.params").addClass("table");
//	$("div.ingroups").wrapInner("<small></small>");
//	$("div.levels").css("margin", "0.5em");
//	$("div.levels > span").addClass("btn btn-default btn-xs");
//	$("div.levels > span").css("margin-right", "0.25em");
//	
//	$("table.directory").addClass("table table-striped");
//	$("div.summary > a").addClass("btn btn-default btn-xs");
//	$("table.fieldtable").addClass("table");
//	$(".fragment").addClass("well");
//	$(".memitem").addClass("panel panel-default");
//	$(".memproto").addClass("panel-heading");
//	$(".memdoc").addClass("panel-body");
//	$("span.mlabel").addClass("label label-info");
//	
//	$("table.memberdecls").addClass("table");
//	$("[class^=memitem]").addClass("active");
//	
//	$("div.ah").addClass("btn btn-default");
//	$("span.mlabels").addClass("pull-right");
//	$("table.mlabels").css("width", "100%")
//	$("td.mlabels-right").addClass("pull-right");
//
//	$("div.ttc").addClass("panel panel-info");
//	$("div.ttname").addClass("panel-heading");
//	$("div.ttdef,div.ttdoc,div.ttdeci").addClass("panel-body");
};

//////////

$(document).ready(bootstrapDoxygen());
