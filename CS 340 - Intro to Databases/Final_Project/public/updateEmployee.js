//Code adapted from instructor's example
function updateEmployee(id){
    $.ajax({
        url: '/employee/' + id,
        type: 'PUT',
        data: $('#update-employee').serialize(),
        success: function(result){
            window.location.replace("./");
        }
    })
};
