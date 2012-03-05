function write_function(d) {
    var funchtml = '';
    
    // Write the function
    funchtml += '<div class="function">\n';
    funchtml += '  <h3>' + _.escape(d.name) + '</h3>\n';
    funchtml += '  <p class="typesig"><code>' + _.escape(d.typesig) + '</code></p>\n';
    funchtml += '  <p class="description">' + _.escape(d.description) + '</p>\n';
    funchtml += '</div>\n';
    
    return funchtml;
}

function write_module(name, functions) {
    var modulehtml = '';
    
    // Write the prefix
    modulehtml += '<div class="module">\n';
    modulehtml += '  <h2>' + _.escape(name) + '</h2>\n';
    
    // Write the functions
    _.each(functions, function (element, index, list) {
        modulehtml += write_function(element);
    });
    
    modulehtml += '</div>\n';
    
    return modulehtml;
}

function write_docs() {

    var bodyhtml = '';
    
    _.each(alldocs, function (value, key, list) {
        bodyhtml += write_module(key, value);
    });
    
    document.getElementById('documentation').innerHTML = bodyhtml;
}
