//Code adapted from instructor's example
function updateDepartment(id){
    $.ajax({
        url: '/department/' + id,
        type: 'PUT',
        data: $('#update-department').serialize(),
        success: function(result){
            window.location.replace("./");
        }
    })
};